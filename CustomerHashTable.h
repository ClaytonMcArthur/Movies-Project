// ------------------------------------------- CustomerHashTable.h ----------------------------------------------------
// Programmer: <Clayton McArthur> 
// Creation Date: <2025-08-21>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose : Lightweight hash table wrapper for Customer* keyed by ID. Owns Customer objects.
// --------------------------------------------------------------------------------------------------------------------

#ifndef CUSTOMERHASHTABLE_H
#define CUSTOMERHASHTABLE_H

#include "Customer.h"
#include <unordered_map>   // hash table for id -> Customer*

class CustomerHashTable
{
public:
    // ------------------------------------------------ addCustomer ---------------------------------------------------
    // Description: Insert or replace an entry for id. Takes ownership of pointer.
    void addCustomer(int customerID, Customer* customer);

    // ------------------------------------------------ getCustomer ---------------------------------------------------
    // Description: Lookup by id; returns nullptr if not found (no ownership transfer).
    Customer* getCustomer(int customerID);

    // -------------------------------------------------- ~CustomerHashTable -----------------------------------------
    // Description: Deletes all owned Customer*.
    ~CustomerHashTable();

private:
    std::unordered_map<int, Customer*> table;
};

#endif // CUSTOMERHASHTABLE_H