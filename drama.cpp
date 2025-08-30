// ------------------------------------------------ drama.cpp ---------------------------------------------------------
// Programmer: <Clayton McArthur>    
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Concrete Drama implementation. Sorts by Director→Title; key = "Director|Title".
// --------------------------------------------------------------------------------------------------------------------

#include "drama.h"
#include "movie.h"
#include <iostream>   // streaming of display()

// ------------------------------------------------- Drama ------------------------------------------------------------
Drama::Drama() : Movie()
{
} // end of Drama default ctor

// ---------------------------------------------- Drama (overload) ---------------------------------------------------
Drama::Drama(const std::string &title, int stock, const std::string &director, int year)
    : Movie(title, stock, director, year)
{
} // end of Drama(value) ctor

// ------------------------------------------------- ~Drama -----------------------------------------------------------
Drama::~Drama()
{
} // end of ~Drama

// ------------------------------------------------- display ----------------------------------------------------------
void Drama::display() const
{
    std::cout << "D, " << stock << ", " << director << ", " << title << ", " << year << std::endl;
} // end of display

// ------------------------------------------------ operator< ---------------------------------------------------------
bool Drama::operator<(const Movie *other) const
{
    const Drama *o = dynamic_cast<const Drama*>(other);
    if (!o) return false;
    if (director != o->director) return director < o->director;
    return title < o->title;
} // end of operator<

// ------------------------------------------------ operator== --------------------------------------------------------
bool Drama::operator==(const Movie *other) const
{
    const Drama *o = dynamic_cast<const Drama*>(other);
    return o && director == o->director && title == o->title;
} // end of operator==

// ------------------------------------------------ getCategory -------------------------------------------------------
char Drama::getCategory() const
{
    return 'D';
} // end of getCategory

// ------------------------------------------------- buildKey ---------------------------------------------------------
std::string Drama::buildKey() const
{
    return director + "|" + title;
} // end of buildKey
