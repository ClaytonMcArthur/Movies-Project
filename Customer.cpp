// -------------------------------------------------- Customer.cpp ----------------------------------------------------
// Programmer: <Clayton McArthur>     
// Creation Date: <2025-08-21>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose : Implements Customer behavior: history printing and outstanding borrow tracking.
// --------------------------------------------------------------------------------------------------------------------

#include "Customer.h"
#include <iostream>

Customer::Customer(int id, const std::string &firstName, const std::string &lastName)
    : id(id),
      firstName(firstName),
      lastName(lastName)
{
}

Customer::~Customer() = default;

void Customer::addHistory(const std::string &transaction)
{
    history.push_back(transaction);
}

void Customer::displayHistory() const
{
    std::cout << "Customer " << id << " " << lastName << ", " << firstName << std::endl;

    if (history.empty())
    {
        std::cout << "  (no transactions)" << std::endl;
        return;
    }

    // Print latest -> earliest
    for (auto it = history.rbegin(); it != history.rend(); ++it)
    {
        std::cout << "  " << *it << std::endl;
    }
}

int Customer::getId() const
{
    return id;
}

bool Customer::hasBorrowed(const std::string &movieKey) const
{
    return borrowedMovies.count(movieKey) > 0;
}

void Customer::borrowMovie(const std::string &movieKey)
{
    borrowedMovies.insert(movieKey);
}

bool Customer::returnMovie(const std::string &movieKey)
{
    auto it = borrowedMovies.find(movieKey);
    if (it == borrowedMovies.end())
    {
        return false;
    }
    borrowedMovies.erase(it);
    return true;
}