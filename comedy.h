// ---------------------------------------------- comedy.h ------------------------------------------------------------
// Programmer: <Davin Til>     
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Comedy movies; ordering by Title then Year. Inventory key is "Title|Year".
// --------------------------------------------------------------------------------------------------------------------

#ifndef COMEDY_H
#define COMEDY_H

#include "movie.h"
#include <string>

class Comedy : public Movie {
public:
    // ------------------------------------------------ Comedy --------------------------------------------------------
    Comedy();

    // ------------------------------------------- Comedy (overload) --------------------------------------------------
    Comedy(const std::string &title, int stock,
           const std::string &director, int year);

    // ---------------------------------------------- ~Comedy ---------------------------------------------------------
    virtual ~Comedy() override;

    // ---------------------------------------------- display ---------------------------------------------------------
    void display() const override;

    // --------------------------------------------- comparisons ------------------------------------------------------
    bool operator<(const Movie *other) const override;
    bool operator==(const Movie *other) const override;

    // ---------------------------------------------- metadata --------------------------------------------------------
    char        getCategory() const override;
    std::string buildKey()    const override;
};

#endif // COMEDY_H