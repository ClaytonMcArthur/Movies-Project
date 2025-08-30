// ------------------------------------------------- Inventory.cpp ----------------------------------------------------
// Programmer: <Marko Flores> 
// Creation Date: <2025-08-22>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose : Implements inventory storage, safe loading with validation, and category-ordered display.
// --------------------------------------------------------------------------------------------------------------------

#include "Inventory.h"
#include "MovieFactory.h"
#include "comedy.h"
#include "drama.h"
#include "classics.h"

#include <fstream>    // std::ifstream
#include <iostream>   // std::cout / std::cerr
#include <sstream>    // std::istringstream
#include <algorithm>  // general utilities
#include <cctype>     // character checks
#include <stdexcept>  // exceptions

// ---------------------------------------------------- helpers -------------------------------------------------------
static inline std::string trim(const std::string &s)
{
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

static inline bool to_int(const std::string &s, int &out)
{
    try
    {
        size_t idx = 0;
        int v = std::stoi(trim(s), &idx);
        if (idx != trim(s).size()) return false;
        out = v;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

// ---------------------------------------------------- ~Inventory ----------------------------------------------------
Inventory::~Inventory()
{
    for (auto &byCat : inventoryMap)
    {
        for (auto &kv : byCat.second)
        {
            delete kv.second;
        }
    }
}

// ---------------------------------------------------- addMovie ------------------------------------------------------
void Inventory::addMovie(Movie* movie)
{
    char cat = movie->getCategory();
    std::string key = movie->buildKey();
    auto &m = inventoryMap[cat];
    auto it = m.find(key);

    if (it == m.end())
    {
        m[key] = movie;
    }
    else
    {
        // Merge by increasing stock
        for (int i = 0; i < movie->getStock(); ++i)
        {
            it->second->increaseStock();
        }
        delete movie;
    }
}

// -------------------------------------------------- borrowMovie -----------------------------------------------------
bool Inventory::borrowMovie(char category, const std::string &key, int /*year*/)
{
    auto byCat = inventoryMap.find(category);
    if (byCat == inventoryMap.end()) return false;

    auto it = byCat->second.find(key);
    if (it == byCat->second.end()) return false;

    return it->second->decreaseStock();
}

// -------------------------------------------------- returnMovie -----------------------------------------------------
bool Inventory::returnMovie(char category, const std::string &key, int /*year*/)
{
    auto byCat = inventoryMap.find(category);
    if (byCat == inventoryMap.end()) return false;

    auto it = byCat->second.find(key);
    if (it == byCat->second.end()) return false;

    it->second->increaseStock();
    return true;
}

// ------------------------------------------------ displayInventory --------------------------------------------------
void Inventory::displayInventory() const
{
    auto printCat = [&](char cat, const std::string &label)
    {
        auto it = inventoryMap.find(cat);
        if (it == inventoryMap.end()) return;

        std::cout << "=== " << label << " ===" << std::endl;
        for (const auto &kv : it->second)
        {
            if (kv.second)
            {
                kv.second->display();
            }
        }
    };

    printCat('F', "Comedy");
    printCat('D', "Drama");
    printCat('C', "Classics");
}

// --------------------------------------------------- loadMovies -----------------------------------------------------
void Inventory::loadMovies(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cerr << "ERROR: cannot open movies file: " << filename << std::endl;
        return;
    }

    std::string line;
    int lineno = 0;

    while (std::getline(fin, line))
    {
        ++lineno;
        std::string raw = trim(line);
        if (raw.empty()) continue;

        // Extract category code and find first comma
        char code = raw[0];
        size_t firstComma = raw.find(',');
        if (firstComma == std::string::npos)
        {
            std::cerr << "ERROR: [" << lineno << "] missing comma after code -> " << raw << std::endl;
            continue;
        }
        if (code != 'F' && code != 'D' && code != 'C')
        {
            std::cerr << "ERROR: [" << lineno << "] invalid movie code '" << code << "' -> " << raw << std::endl;
            continue;
        }

        // rest after "code,"
        std::string rest = trim(raw.substr(firstComma + 1));

        // Split the first three comma-separated tokens: stock, director, title
        size_t c1 = rest.find(',');
        size_t c2 = (c1 == std::string::npos) ? std::string::npos : rest.find(',', c1 + 1);
        if (c1 == std::string::npos || c2 == std::string::npos)
        {
            std::cerr << "ERROR: [" << lineno << "] not enough fields -> " << raw << std::endl;
            continue;
        }
        std::string stock_s  = trim(rest.substr(0, c1));
        std::string director = trim(rest.substr(c1 + 1, c2 - (c1 + 1)));
        std::string title    = trim(rest.substr(c2 + 1));

        // For classics, 'title' may still contain ", ActorFirst ActorLast month year"
        size_t c3 = title.find(',');
        std::string tail;
        if (c3 != std::string::npos)
        {
            tail  = trim(title.substr(c3 + 1));
            title = trim(title.substr(0, c3));
        }

        int stock = 0;
        if (!to_int(stock_s, stock) || stock < 0)
        {
            std::cerr << "ERROR: [" << lineno << "] invalid stock -> " << raw << std::endl;
            continue;
        }

        try
        {
            if (code == 'F' || code == 'D')
            {
                // tail should be the year for F/D
                int year = 0;
                if (!to_int(tail, year))
                {
                    std::cerr << "ERROR: [" << lineno << "] invalid year -> " << raw << std::endl;
                    continue;
                }

                Movie *m = (code == 'F')
                    ? static_cast<Movie*>(new Comedy(title, stock, director, year))
                    : static_cast<Movie*>(new Drama(title, stock, director, year));
                addMovie(m);
            }
            else
            {
                // Classics: tail = "ActorFirst ActorLast month year"
                std::istringstream tss(tail);
                std::string actorFirst, actorLast;
                int month = 0, year = 0;

                if (!(tss >> actorFirst >> actorLast >> month >> year))
                {
                    std::cerr << "ERROR: [" << lineno << "] invalid classics tail -> " << raw << std::endl;
                    continue;
                }
                if (month < 1 || month > 12)
                {
                    std::cerr << "ERROR: [" << lineno << "] invalid month -> " << raw << std::endl;
                    continue;
                }

                Movie *m = new Classics(title, stock, director, month, year, actorFirst, actorLast);
                addMovie(m);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "ERROR: [" << lineno << "] exception: " << e.what() << " -> " << raw << std::endl;
            continue;
        }
        catch (...)
        {
            std::cerr << "ERROR: [" << lineno << "] unknown exception -> " << raw << std::endl;
            continue;
        }
    }
}