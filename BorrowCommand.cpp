// ---------------------------------------------- BorrowCommand.cpp ---------------------------------------------------
// Borrows a movie for a customer if available; logs to history and marks outstanding borrow.

#include "BorrowCommand.h"
#include "Inventory.h"
#include "CustomerHashTable.h"
#include "Customer.h"
#include <iostream>
#include <sstream>

// --------------------------------------------------------------------------------------------------------------
// keyFor
// Description: Build the inventory key for a given category + fields, matching Movie::buildKey() semantics.
// --------------------------------------------------------------------------------------------------------------
static std::string keyFor(char type, const std::string &title, int year,
                          const std::string &director, int month, const std::string &actor)
{
    if (type == 'F')
    {
        std::ostringstream oss;
        oss << title << "|" << year;
        return oss.str();
    }
    if (type == 'D')
    {
        return director + "|" + title;
    }
    // Classics
    std::ostringstream oss;
    oss << year << "-";
    if (month < 10) oss << "0";
    oss << month << "|" << actor;
    return oss.str();
}

BorrowCommand::BorrowCommand(int id, char category, const std::string &title,
                             int year, const std::string &director)
    : customerID(id),
      movieType(category),
      title(title),
      year(year),
      director(director),
      month(0),
      actor("")
{
}

BorrowCommand::BorrowCommand(int id, char category, int month, int year, const std::string &actorFull)
    : customerID(id),
      movieType(category),
      title(""),
      year(year),
      director(""),
      month(month),
      actor(actorFull)
{
}

void BorrowCommand::execute(Inventory &inventory, CustomerHashTable &customers) const
{
    Customer *cust = customers.getCustomer(customerID);
    if (!cust)
    {
        std::cerr << "ERROR: Unknown customer ID " << customerID << std::endl;
        return;
    }

    const std::string key = keyFor(movieType, title, year, director, month, actor);
    const bool ok = inventory.borrowMovie(movieType, key, year);
    if (!ok)
    {
        std::cerr << "ERROR: Borrow failed for customer " << customerID
                  << " movieType " << movieType << " key '" << key << "'" << std::endl;
        return;
    }

    cust->borrowMovie(key);
    std::ostringstream h;
    h << "Borrow " << movieType << " [" << key << "]";
    cust->addHistory(h.str());
}