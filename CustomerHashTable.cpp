// ------------------------------------------- CustomerHashTable.cpp --------------------------------------------------
// Programmer: <Clayton McArthur>    
// Creation Date: <2025-08-21>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose : Ownership-aware hash map of customers by ID.
// --------------------------------------------------------------------------------------------------------------------

#include "CustomerHashTable.h"
#include <utility>

void CustomerHashTable::addCustomer(int customerID, Customer* customer)
{
    table[customerID] = customer;
}

Customer* CustomerHashTable::getCustomer(int customerID)
{
    auto it = table.find(customerID);
    return (it == table.end()) ? nullptr : it->second;
}

CustomerHashTable::~CustomerHashTable()
{
    for (auto &kv : table)
    {
        delete kv.second;
    }
}