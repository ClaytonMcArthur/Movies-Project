// ----------------------------------------------- movie.h -----------------------------------------------------------
// Programmer: <Davin Til>     
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Abstract base class for all Movie types (Comedy, Drama, Classics). Holds common fields (title, stock,
//          director, year) and defines the polymorphic interface for display, comparison, category, and key building.
// Notes :  - Virtual destructor for safe polymorphic deletion.
//          - No global variables; only class members (per course standards).
//          - operator<< is declared; implementation calls display() in movie.cpp.
// --------------------------------------------------------------------------------------------------------------------

#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>   // std::ostream for operator<<
#include <string>     // std::string for titles, directors, keys

class Movie {
public:
    // ---------------------------------------------- Movie -----------------------------------------------------------
    // Description: Default-constructs an empty Movie with zero stock.
    // ----------------------------------------------------------------------------------------------------------------
    Movie();

    // ------------------------------------------- Movie (overload) ---------------------------------------------------
    // Description: Construct a Movie with common attributes.
    // ----------------------------------------------------------------------------------------------------------------
    Movie(const std::string &title, int stock,
          const std::string &director, int year);

    // -------------------------------------------- ~Movie ------------------------------------------------------------
    // Description: Virtual destructor for proper cleanup via base pointer.
    // ----------------------------------------------------------------------------------------------------------------
    virtual ~Movie();

    // ----------------------------------------- decreaseStock --------------------------------------------------------
    // Description: If stock > 0, decrement stock and return true; otherwise return false.
    // ----------------------------------------------------------------------------------------------------------------
    virtual bool decreaseStock();

    // ----------------------------------------- increaseStock --------------------------------------------------------
    // Description: Increment stock by one. No preconditions.
    // ----------------------------------------------------------------------------------------------------------------
    virtual void increaseStock();

    // --------------------------------------------- display ----------------------------------------------------------
    // Description: Print a concrete Movie’s details. Must be implemented by derived types.
    // ----------------------------------------------------------------------------------------------------------------
    virtual void display() const = 0;

    // -------------------------------------- comparison / identity ---------------------------------------------------
    // Description: Polymorphic comparisons required by inventory sorting and equality checks.
    // ----------------------------------------------------------------------------------------------------------------
    virtual bool operator<(const Movie *other) const = 0;
    virtual bool operator==(const Movie *other) const = 0;

    // -------------------------------------------- metadata ----------------------------------------------------------
    // Description: Category character ('F','D','C') and canonical inventory key for lookups/merges.
    // ----------------------------------------------------------------------------------------------------------------
    virtual char        getCategory() const = 0;
    virtual std::string buildKey()    const = 0;

    // -------------------------------------------- accessors ---------------------------------------------------------
    std::string getTitle()    const;
    int         getYear()     const;
    std::string getDirector() const;
    int         getStock()    const;

protected:
    std::string title;
    int         stock;
    std::string director;
    int         year;
};

// ------------------------------------------- operator<< -------------------------------------------------------------
// Description: Stream insertion that delegates to display() so all movies print consistently.
// --------------------------------------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const Movie &movie);

#endif // MOVIE_H