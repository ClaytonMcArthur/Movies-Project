// ---------------------------------------------- movie.cpp -----------------------------------------------------------
// Programmer: <Clayton McArthur>     
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Implements common Movie behavior (stock management, accessors) and operator<<.
// --------------------------------------------------------------------------------------------------------------------

#include "movie.h"
#include <iostream>
#include <string>

// ------------------------------------------------ Movie -------------------------------------------------------------
Movie::Movie()
{
    this->title    = "";
    this->stock    = 0;
    this->director = "";
    this->year     = 0;
} // end of Movie default ctor

// --------------------------------------------- Movie (overload) ----------------------------------------------------
Movie::Movie(const std::string &title, int stock, const std::string &director, int year)
{
    this->title    = title;
    this->stock    = stock;
    this->director = director;
    this->year     = year;
} // end of Movie(value) ctor

// ------------------------------------------------ ~Movie ------------------------------------------------------------
Movie::~Movie()
{
} // end of ~Movie

// ---------------------------------------------- decreaseStock ------------------------------------------------------
bool Movie::decreaseStock()
{
    if (stock > 0)
    {
        stock -= 1;
        return true;
    }
    return false;
} // end of decreaseStock

// ---------------------------------------------- increaseStock ------------------------------------------------------
void Movie::increaseStock()
{
    stock += 1;
} // end of increaseStock

// ------------------------------------------------ accessors --------------------------------------------------------
std::string Movie::getTitle() const
{
    return this->title;
} // end of getTitle

int Movie::getYear() const
{
    return this->year;
} // end of getYear

std::string Movie::getDirector() const
{
    return this->director;
} // end of getDirector

int Movie::getStock() const
{
    return this->stock;
} // end of getStock

// ---------------------------------------------- operator<< ---------------------------------------------------------
// Calls the virtual display() so each subclass determines its printed format.
std::ostream &operator<<(std::ostream &os, const Movie &movie)
{
    movie.display();
    return os;
} // end of operator<<
