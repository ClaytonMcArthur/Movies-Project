// -------------------------------------------------- Customer.h ------------------------------------------------------
// Programmer: <Clayton McArthur>     
// Creation Date: <2025-08-21>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose : Represents a store customer. Tracks ID, name, transaction history, and currently-borrowed items.
// --------------------------------------------------------------------------------------------------------------------

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>     // displayHistory()
#include <set>          // borrowed set
#include <string>
#include <vector>       // history list

class Customer
{
public:
    // -------------------------------------------------- Customer ----------------------------------------------------
    Customer(int id, const std::string &firstName, const std::string &lastName);

    // ------------------------------------------------- ~Customer ----------------------------------------------------
    virtual ~Customer();

    // ------------------------------------------------ addHistory ----------------------------------------------------
    // Description: Append a human-readable transaction line.
    void addHistory(const std::string &transaction);

    // ---------------------------------------------- displayHistory --------------------------------------------------
    // Description: Prints customer line + recent transactions (newest first) or "(no transactions)".
    void displayHistory() const;

    // --------------------------------------------------- getId ------------------------------------------------------
    int getId() const;

    // ---------------------------------------- borrow/return helpers -------------------------------------------------
    bool hasBorrowed(const std::string &movieKey) const;
    void borrowMovie(const std::string &movieKey);
    bool returnMovie(const std::string &movieKey);

private:
    int                      id;
    std::string              firstName;
    std::string              lastName;
    std::vector<std::string> history;        // append oldest->newest, print newest-first
    std::set<std::string>    borrowedMovies; // outstanding borrow set
};

#endif // CUSTOMER_H