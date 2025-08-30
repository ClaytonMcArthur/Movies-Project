// -------------------------------------------------- main.cpp --------------------------------------------------------
// Programmer: <Clayton McArthur>     
// Creation Date: <2025-08-23>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose : Test driver that loads movies/customers, parses and executes commands, logs executed lines,
//           prints inventory/history output to stdout, and validation/errors to stderr.
// Usage   : ./movies_tester [moviesFile] [customersFile] [commandsFile] [completedLogFile]
//           Defaults: data4movies.txt, data4customers.txt, data4commands.txt, completed_commands.txt
// --------------------------------------------------------------------------------------------------------------------

#include "Inventory.h"
#include "CustomerHashTable.h"
#include "Customer.h"
#include "CommandFactory.h"

#include <fstream>     // file I/O
#include <iostream>    // std::cout/std::cerr
#include <sstream>
#include <string>
#include <exception>

// ---------------------------------------------------- trim ----------------------------------------------------------
static inline std::string trim(const std::string &s)
{
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

// ---------------------------------------------------- main ----------------------------------------------------------
int main(int argc, char** argv) try
{
    std::string moviesFile    = "data4movies.txt";
    std::string customersFile = "data4customers.txt";
    std::string commandsFile  = "data4commands.txt";
    std::string completedLog  = "completed_commands.txt";

    if (argc >= 4)
    {
        moviesFile    = argv[1];
        customersFile = argv[2];
        commandsFile  = argv[3];
    }
    if (argc >= 5)
    {
        completedLog  = argv[4];
    }

    std::cerr << "[info] Movies: "     << moviesFile
              << " | Customers: "      << customersFile
              << " | Commands: "       << commandsFile
              << " | Completed log: "  << completedLog << std::endl;

    // Open completed-commands log (truncate).
    std::ofstream completed(completedLog);
    if (!completed)
    {
        std::cerr << "ERROR: cannot open completed log file for write: " << completedLog << std::endl;
        return 1;
    }
    completed << "# Completed (parsed & executed) commands\n";

    // Load inventory.
    Inventory inventory;
    inventory.loadMovies(moviesFile);

    // Load customers.
    CustomerHashTable customers;
    {
        std::ifstream fin(customersFile);
        if (!fin)
        {
            std::cerr << "ERROR: cannot open customers file: " << customersFile << std::endl;
            return 1;
        }
        int id; std::string last, first;
        while (fin >> id >> last >> first)
        {
            customers.addCustomer(id, new Customer(id, first, last));
        }
    }

    // Process commands (line by line).
    std::ifstream fin(commandsFile);
    if (!fin)
    {
        std::cerr << "ERROR: cannot open commands file: " << commandsFile << std::endl;
        return 1;
    }

    std::string line;
    int lineNo = 0, executed = 0, skipped = 0;

    while (std::getline(fin, line))
    {
        ++lineNo;
        if (trim(line).empty()) continue;

        Command *cmd = CommandFactory::createCommand(line);
        if (!cmd)
        {
            ++skipped;
            continue;
        }

        try
        {
            cmd->execute(inventory, customers);
            completed << line << "\n";   // record only parsed+executed commands
            ++executed;
        }
        catch (const std::exception &e)
        {
            std::cerr << "ERROR: [command line " << lineNo << "] exception: " << e.what()
                      << " while executing -> " << line << std::endl;
        }
        catch (...)
        {
            std::cerr << "ERROR: [command line " << lineNo << "] unknown exception while executing -> "
                      << line << std::endl;
        }

        delete cmd;
    }

    std::cerr << "[info] Commands executed: " << executed
              << " | skipped/malformed: "    << skipped << std::endl;

    return 0;
}
catch (const std::exception &e)
{
    std::cerr << "[fatal] Uncaught exception: " << e.what() << std::endl;
    return 2;
}
catch (...)
{
    std::cerr << "[fatal] Uncaught unknown exception." << std::endl;
    return 3;
}