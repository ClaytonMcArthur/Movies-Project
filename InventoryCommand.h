// --------------------------------------------- InventoryCommand.h ---------------------------------------------------
// Programmer: <Clayton McArthur> 
// Creation Date: <2025-08-21>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Command that prints the entire inventory in category order (Comedy, Drama, Classics).
// --------------------------------------------------------------------------------------------------------------------

#ifndef INVENTORYCOMMAND_H
#define INVENTORYCOMMAND_H

#include "Command.h"

class Inventory;  // fwd decl

class InventoryCommand : public Command
{
public:
    InventoryCommand() = default;
    ~InventoryCommand() override = default;

    // --------------------------------------------------------------------------------------------------------------
    // execute
    // Post: Calls Inventory::displayInventory() to print all movies in required order/format.
    // --------------------------------------------------------------------------------------------------------------
    void execute(Inventory &inventory, CustomerHashTable &customers) const override;
};

#endif // INVENTORYCOMMAND_H