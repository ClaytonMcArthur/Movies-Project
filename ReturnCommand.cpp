// --------------------------------------------- ReturnCommand.cpp ----------------------------------------------------
// Programmer: <Clayton McArthur>
// Creation Date: <2025-08-21>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose : Returns a movie for a customer if it was previously borrowed; updates inventory and customer history.
// --------------------------------------------------------------------------------------------------------------------

#include "ReturnCommand.h"
#include "Inventory.h"
#include "CustomerHashTable.h"
#include "Customer.h"
#include <iostream>   // error/status messages
#include <sstream>    // formatting keys

// ------------------------------------------------ keyForR -----------------------------------------------------------
// Description: Build canonical inventory key matching Movie::buildKey() semantics.
// --------------------------------------------------------------------------------------------------------------------
static std::string keyForR(char type,
                           const std::string &title,
                           int year,
                           const std::string &director,
                           int month,
                           const std::string &actor)
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

// -------------------------------------------- ReturnCommand (F/D) ---------------------------------------------------
ReturnCommand::ReturnCommand(int id, char category, const std::string &title,
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

// --------------------------------------------- ReturnCommand (C) ----------------------------------------------------
ReturnCommand::ReturnCommand(int id, char category, int month, int year, const std::string &actorFull)
    : customerID(id),
      movieType(category),
      title(""),
      year(year),
      director(""),
      month(month),
      actor(actorFull)
{
}

// -------------------------------------------------- execute ---------------------------------------------------------
void ReturnCommand::execute(Inventory &inventory, CustomerHashTable &customers) const
{
    Customer *cust = customers.getCustomer(customerID);
    if (!cust)
    {
        std::cerr << "ERROR: Unknown customer ID " << customerID << std::endl;
        return;
    }

    const std::string key = keyForR(movieType, title, year, director, month, actor);

    // Ensure the customer actually borrowed this title.
    if (!cust->returnMovie(key))
    {
        std::cerr << "ERROR: Return failed: customer " << customerID
                  << " did not borrow [" << key << "]" << std::endl;
        return;
    }

    // Return to inventory.
    if (!inventory.returnMovie(movieType, key, year))
    {
        std::cerr << "ERROR: Return failed for inventory for key '" << key << "'" << std::endl;
        return;
    }

    // Record in transaction history.
    std::ostringstream h;
    h << "Return " << movieType << " [" << key << "]";
    cust->addHistory(h.str());
}