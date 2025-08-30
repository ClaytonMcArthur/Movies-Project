// ---------------------------------------------- HistoryCommand.cpp --------------------------------------------------
// Prints a customer's transaction history.

#include "HistoryCommand.h"
#include "CustomerHashTable.h"
#include "Customer.h"
#include <iostream>

void HistoryCommand::execute(Inventory &, CustomerHashTable &customers) const
{
    Customer *c = customers.getCustomer(customerID);
    if (!c)
    {
        std::cerr << "ERROR: Unknown customer ID " << customerID << std::endl;
        return;
    }
    c->displayHistory();
}