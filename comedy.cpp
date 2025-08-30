// ---------------------------------------------- comedy.cpp ----------------------------------------------------------
// Programmer: <Davin Til>     
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Concrete Comedy implementation. Sorts by Title→Year; key = "Title|Year".
// --------------------------------------------------------------------------------------------------------------------

#include "comedy.h"
#include "movie.h"
#include <iostream>   // streaming of display()
#include <sstream>    // key formatting

// ------------------------------------------------ Comedy ------------------------------------------------------------
Comedy::Comedy() : Movie()
{
} // end of Comedy default ctor

// --------------------------------------------- Comedy (overload) ---------------------------------------------------
Comedy::Comedy(const std::string &title, int stock, const std::string &director, int year)
    : Movie(title, stock, director, year)
{
} // end of Comedy(value) ctor

// ------------------------------------------------ ~Comedy -----------------------------------------------------------
Comedy::~Comedy()
{
} // end of ~Comedy

// ------------------------------------------------ display -----------------------------------------------------------
void Comedy::display() const
{
    std::cout << "F, " << stock << ", " << director << ", " << title << ", " << year << std::endl;
} // end of display

// ----------------------------------------------- operator< ----------------------------------------------------------
bool Comedy::operator<(const Movie *other) const
{
    const Comedy *o = dynamic_cast<const Comedy*>(other);
    if (!o) return false;                    // define cross-type ordering
    if (title != o->title) return title < o->title;
    return year < o->year;
} // end of operator<

// ---------------------------------------------- operator== ----------------------------------------------------------
bool Comedy::operator==(const Movie *other) const
{
    const Comedy *o = dynamic_cast<const Comedy*>(other);
    return o && title == o->title && year == o->year;
} // end of operator==

// ---------------------------------------------- getCategory ---------------------------------------------------------
char Comedy::getCategory() const
{
    return 'F';
} // end of getCategory

// ----------------------------------------------- buildKey -----------------------------------------------------------
std::string Comedy::buildKey() const
{
    std::ostringstream oss;
    oss << title << "|" << year;
    return oss.str();
} // end of buildKey