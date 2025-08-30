// --------------------------------------------- CommandFactory.cpp ---------------------------------------------------
// Parses lines of the form:
//   I
//   H <id>
//   B <id> D <type> <descriptor...>
//   R <id> D <type> <descriptor...>
// Where <type> is 'F','D','C' and media is 'D' (DVD). Invalid lines are reported and skipped.

#include "CommandFactory.h"
#include "InventoryCommand.h"
#include "HistoryCommand.h"
#include "BorrowCommand.h"
#include "ReturnCommand.h"
#include <sstream>
#include <iostream>
#include <cctype>
#include <stdexcept>

// ----------------------------------------------- helpers ------------------------------------------------------------
static inline std::string trim(const std::string &s)
{
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

static inline std::string rtrimComma(const std::string &s)
{
    std::string t = trim(s);
    if (!t.empty() && t.back() == ',') t.pop_back();
    return trim(t);
}

// Registry access
std::map<char, std::function<Command*(const std::string&)>>& CommandFactory::getRegistry()
{
    static std::map<char, std::function<Command*(const std::string&)>> reg;
    return reg;
}

void CommandFactory::registerCommand(char commandType,
                                     std::function<Command*(const std::string&)> creator)
{
    getRegistry()[commandType] = std::move(creator);
}

// ----------------------------------------- concrete parser functions ------------------------------------------------
static Command* parseInventory(const std::string &)
{
    return new InventoryCommand();
}

static Command* parseHistory(const std::string &line)
{
    std::istringstream ss(line);
    char code; int id;
    if (!(ss >> code >> id))
    {
        std::cerr << "ERROR: bad History command: " << line << std::endl;
        return nullptr;
    }
    return new HistoryCommand(id);
}

static Command* parseBorrowOrReturn(const std::string &line, bool isBorrow)
{
    std::istringstream ss(line);
    char code; int customerId; char media; char type;
    if (!(ss >> code >> customerId >> media >> type))
    {
        std::cerr << "ERROR: bad command: " << line << std::endl;
        return nullptr;
    }
    if (media != 'D')
    {
        std::cerr << "ERROR: invalid media type '" << media << "' in: " << line << std::endl;
        return nullptr;
    }

    std::string rest; std::getline(ss, rest);
    rest = trim(rest);

    try
    {
        if (type == 'F')
        {
            // Title, Year
            size_t comma = rest.rfind(',');
            if (comma == std::string::npos)
            {
                std::cerr << "ERROR: bad Comedy command: " << line << std::endl;
                return nullptr;
            }
            std::string title = trim(rest.substr(0, comma));
            int year = std::stoi(trim(rest.substr(comma + 1)));
            if (isBorrow) return new BorrowCommand(customerId, type, title, year, /*director*/"");
            else          return new ReturnCommand(customerId, type, title, year, /*director*/"");
        }
        else if (type == 'D')
        {
            // Director, Title,
            size_t comma1 = rest.find(',');
            if (comma1 == std::string::npos)
            {
                std::cerr << "ERROR: bad Drama command: " << line << std::endl;
                return nullptr;
            }
            std::string director = trim(rest.substr(0, comma1));
            std::string title    = rtrimComma(rest.substr(comma1 + 1));
            if (isBorrow) return new BorrowCommand(customerId, type, title, /*year*/0, director);
            else          return new ReturnCommand(customerId, type, title, /*year*/0, director);
        }
        else if (type == 'C')
        {
            // month year First Last
            std::istringstream tss(rest);
            int month, year; std::string first, last;
            if (!(tss >> month >> year >> first >> last))
            {
                std::cerr << "ERROR: bad Classics command: " << line << std::endl;
                return nullptr;
            }
            std::string actor = first + " " + last;
            if (isBorrow) return new BorrowCommand(customerId, type, month, year, actor);
            else          return new ReturnCommand(customerId, type, month, year, actor);
        }
        else
        {
            std::cerr << "ERROR: invalid movie code '" << type << "' in: " << line << std::endl;
            return nullptr;
        }
    }
    catch (const std::exception &)
    {
        std::cerr << "ERROR: numeric parse failure in: " << line << std::endl;
        return nullptr;
    }
}

static Command* parseBorrow(const std::string &line) { return parseBorrowOrReturn(line, true);  }
static Command* parseReturn(const std::string &line) { return parseBorrowOrReturn(line, false); }

// ------------------------------------------ static registration -----------------------------------------------------
static bool ensureRegistered()
{
    CommandFactory::registerCommand('I', parseInventory);
    CommandFactory::registerCommand('H', parseHistory);
    CommandFactory::registerCommand('B', parseBorrow);
    CommandFactory::registerCommand('R', parseReturn);
    return true;
}

// Force static initialization
static const bool registered = ensureRegistered();

// ---------------------------------------------- createCommand -------------------------------------------------------
Command* CommandFactory::createCommand(const std::string &line)
{
    std::string s = trim(line);
    if (s.empty()) return nullptr;

    char type = s[0];
    auto it = getRegistry().find(type);
    if (it == getRegistry().end())
    {
        std::cerr << "ERROR: invalid action code '" << type << "' in: " << line << std::endl;
        return nullptr;
    }
    return it->second(line);
}