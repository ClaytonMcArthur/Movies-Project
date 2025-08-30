// -------------------------------------------------- Command.h -------------------------------------------------------
// Programmer: <Clayton McArthur>     
// Creation Date: <2025-08-20>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Abstract base for all command types (Inventory, History, Borrow, Return).
//          Provides a pure-virtual execute() to be implemented by concrete commands.
// Notes   : - Virtual destructor for safe polymorphic deletion.
//           - No global variables. Minimal header-only base to avoid extra translation unit.
// --------------------------------------------------------------------------------------------------------------------

#ifndef COMMAND_H
#define COMMAND_H

class CustomerHashTable;   // fwd decl to avoid heavy includes in the interface
class Inventory;           // fwd decl

class Command
{
public:
    virtual ~Command() {}  // header-only to keep Command.cpp optional
    // --------------------------------------------------------------------------------------------------------------
    // execute
    // Pre : Inventory and customer table are constructed/loaded.
    // Post: Performs the command’s action (may print to stdout/stderr, update state, etc.).
    // --------------------------------------------------------------------------------------------------------------
    virtual void execute(Inventory &inventory, CustomerHashTable &customers) const = 0;
};

#endif // COMMAND_H