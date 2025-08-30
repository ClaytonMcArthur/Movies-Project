// ----------------------------------------------- drama.h ------------------------------------------------------------
// Programmer: <Clayton McArthur>     
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Drama movies; ordering by Director then Title. Key is "Director|Title".
// --------------------------------------------------------------------------------------------------------------------

#ifndef DRAMA_H
#define DRAMA_H

#include "movie.h"
#include <string>

class Drama : public Movie {
public:
    // ------------------------------------------------ Drama ---------------------------------------------------------
    Drama();

    // -------------------------------------------- Drama (overload) --------------------------------------------------
    Drama(const std::string &title, int stock,
          const std::string &director, int year);

    // ------------------------------------------------ ~Drama --------------------------------------------------------
    virtual ~Drama() override;

    // ------------------------------------------------ display -------------------------------------------------------
    void display() const override;

    // --------------------------------------------- comparisons ------------------------------------------------------
    bool operator<(const Movie *other) const override;
    bool operator==(const Movie *other) const override;

    // ------------------------------------------------ metadata ------------------------------------------------------
    char        getCategory() const override;
    std::string buildKey()    const override;
};

#endif // DRAMA_H
