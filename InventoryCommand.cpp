// --------------------------------------------- InventoryCommand.cpp -------------------------------------------------
// Prints the store’s current inventory.

#include "InventoryCommand.h"
#include "Inventory.h"

void InventoryCommand::execute(Inventory &inventory, CustomerHashTable &) const
{
    inventory.displayInventory();
}