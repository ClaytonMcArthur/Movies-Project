// ---------------------------------------------- HistoryCommand.h ----------------------------------------------------
// Programmer: <Clayton McArthur>   
// Creation Date: <2025-08-21>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Command that prints a single customer's transaction history (latest first).
// --------------------------------------------------------------------------------------------------------------------

#ifndef HISTORY_COMMAND_H
#define HISTORY_COMMAND_H

#include "Command.h"

class HistoryCommand : public Command
{
public:
    explicit HistoryCommand(int id)
        : customerID(id)
    {
    }

    // --------------------------------------------------------------------------------------------------------------
    // execute
    // Post: If the customer exists, prints their history (or "(no transactions)"); otherwise logs an error.
    // --------------------------------------------------------------------------------------------------------------
    void execute(Inventory &inventory, CustomerHashTable &customers) const override;

private:
    int customerID;
};

#endif // HISTORY_COMMAND_H