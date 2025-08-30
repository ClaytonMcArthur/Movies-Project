// ---------------------------------------------- BorrowCommand.h -----------------------------------------------------
// Programmer: <Clayton McArthur>     
// Creation Date: <2025-08-20>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Command that borrows a movie for a given customer. Supports Comedy (F), Drama (D), Classics (C).
// Notes  : Uses canonical keys consistent with Inventory/Movie buildKey():
//          - F: "Title|Year"
//          - D: "Director|Title"
//          - C: "YYYY-MM|First Last"
// --------------------------------------------------------------------------------------------------------------------

#ifndef BORROWCOMMAND_H
#define BORROWCOMMAND_H

#include "Command.h"
#include <string>

class BorrowCommand : public Command
{
public:
    // Non-Classics: Comedy/Drama constructor
    BorrowCommand(int id, char category, const std::string &title,
                  int year, const std::string &director);

    // Classics constructor
    BorrowCommand(int id, char category, int month, int year, const std::string &actorFull);

    // --------------------------------------------------------------------------------------------------------------
    // execute
    // Post: If customer exists and stock is available, decrements stock, records transaction, and marks as borrowed.
    //       Otherwise logs an error with the reason (unknown customer, unknown movie, out of stock, etc.).
    // --------------------------------------------------------------------------------------------------------------
    void execute(Inventory &inventory, CustomerHashTable &customers) const override;

private:
    int         customerID;
    char        movieType;   // 'F','D','C'

    // F/D fields
    std::string title;
    int         year;
    std::string director;

    // C fields
    int         month;
    std::string actor;       // "First Last"
};

#endif // BORROWCOMMAND_H