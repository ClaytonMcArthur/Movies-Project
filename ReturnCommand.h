// --------------------------------------------- ReturnCommand.h ------------------------------------------------------
// Programmer: <Clayton McArthur>    
// Creation Date: <2025-08-21>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose : Command that returns a movie for a given customer. Supports Comedy (F), Drama (D), Classics (C).
// Notes   : Uses the same canonical keys as Inventory/Movie::buildKey():
//           - F: "Title|Year"
//           - D: "Director|Title"
//           - C: "YYYY-MM|First Last"
// --------------------------------------------------------------------------------------------------------------------

#ifndef RETURNCOMMAND_H
#define RETURNCOMMAND_H

#include "Command.h"
#include <string>

class Inventory;           // fwd decl
class CustomerHashTable;   // fwd decl

class ReturnCommand : public Command
{
public:
    // ------------------------------------------ ReturnCommand (F/D) -------------------------------------------------
    // Description: Construct a return for Comedy/Drama.
    ReturnCommand(int id, char category, const std::string &title,
                  int year, const std::string &director);

    // ------------------------------------------ ReturnCommand (C) ---------------------------------------------------
    // Description: Construct a return for Classics.
    ReturnCommand(int id, char category, int month, int year, const std::string &actorFull);

    // ------------------------------------------------ execute -------------------------------------------------------
    // Pre : Inventory and customers loaded; IDs and keys are consistent with Inventory.
    // Post: If the customer had borrowed this movie, it is returned to inventory and logged in history.
    void execute(Inventory &inventory, CustomerHashTable &customers) const override;

private:
    int         customerID;
    char        movieType;     // 'F','D','C'

    // F/D fields
    std::string title;
    int         year;
    std::string director;

    // C fields
    int         month;
    std::string actor;         // "First Last"
};

#endif // RETURNCOMMAND_H