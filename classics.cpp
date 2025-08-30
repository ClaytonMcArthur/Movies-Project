// ---------------------------------------------- classics.cpp --------------------------------------------------------
// Programmer: <Davin Til>     
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Concrete Classics implementation. Sorts by Year→Month→Actor; key = "YYYY-MM|First Last".
// --------------------------------------------------------------------------------------------------------------------

#include "classics.h"
#include "movie.h"
#include <iostream>   // streaming of display()
#include <sstream>    // key formatting
#include <iomanip>    // std::setw, std::setfill for zero-padded month (per spec)

// ------------------------------------------------ Classics ----------------------------------------------------------
Classics::Classics() : Movie(), releaseMonth(0), majorActorFirst(""), majorActorLast("")
{
} // end of Classics default ctor

// ------------------------------------------- Classics (overload) ----------------------------------------------------
Classics::Classics(const std::string &title, int stock, const std::string &director,
                   int releaseMonth, int year,
                   const std::string &majorActorFirst, const std::string &majorActorLast)
    : Movie(title, stock, director, year),
      releaseMonth(releaseMonth),
      majorActorFirst(majorActorFirst),
      majorActorLast(majorActorLast)
{
} // end of Classics(value) ctor

// ------------------------------------------------ ~Classics ---------------------------------------------------------
Classics::~Classics()
{
} // end of ~Classics

// ------------------------------------------------- display ----------------------------------------------------------
void Classics::display() const
{
    std::cout << "C, " << stock << ", " << director << ", " << title << ", "
              << majorActorFirst << " " << majorActorLast << " "
              << releaseMonth << " " << year << std::endl;
} // end of display

// ------------------------------------------------ operator< ---------------------------------------------------------
bool Classics::operator<(const Movie *other) const
{
    const Classics *o = dynamic_cast<const Classics*>(other);
    if (!o) return false;
    if (year != o->year) return year < o->year;
    if (releaseMonth != o->releaseMonth) return releaseMonth < o->releaseMonth;
    const std::string a = majorActorFirst + " " + majorActorLast;
    const std::string b = o->majorActorFirst + " " + o->majorActorLast;
    return a < b;
} // end of operator<

// ------------------------------------------------ operator== --------------------------------------------------------
bool Classics::operator==(const Movie *other) const
{
    const Classics *o = dynamic_cast<const Classics*>(other);
    return o && year == o->year
             && releaseMonth == o->releaseMonth
             && majorActorFirst == o->majorActorFirst
             && majorActorLast  == o->majorActorLast;
} // end of operator==

// ------------------------------------------------ getCategory -------------------------------------------------------
char Classics::getCategory() const
{
    return 'C';
} // end of getCategory

// ------------------------------------------------- buildKey ---------------------------------------------------------
std::string Classics::buildKey() const
{
    std::ostringstream oss;
    oss << year << "-" << std::setw(2) << std::setfill('0') << releaseMonth
        << "|" << majorActorFirst << " " << majorActorLast;
    return oss.str();
} // end of buildKey

// ------------------------------------------------- accessors --------------------------------------------------------
int Classics::getReleaseMonth() const
{
    return releaseMonth;
} // end of getReleaseMonth

std::string Classics::getMajorActorFirst() const
{
    return majorActorFirst;
} // end of getMajorActorFirst

std::string Classics::getMajorActorLast() const
{
    return majorActorLast;
} // end of getMajorActorLast