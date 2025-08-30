// ---------------------------------------------- classics.h ----------------------------------------------------------
// Programmer: <Davin Til>     
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Classics movies; ordering by Year→Month→Major Actor. Key is "YYYY-MM|First Last".
// --------------------------------------------------------------------------------------------------------------------

#ifndef CLASSICS_H
#define CLASSICS_H

#include "movie.h"
#include <string>

class Classics : public Movie {
public:
    // ------------------------------------------------ Classics ------------------------------------------------------
    Classics();

    // ------------------------------------------ Classics (overload) -------------------------------------------------
    Classics(const std::string &title, int stock,
             const std::string &director, int releaseMonth,
             int year, const std::string &majorActorFirst, const std::string &majorActorLast);

    // ------------------------------------------------ ~Classics -----------------------------------------------------
    virtual ~Classics() override;

    // ------------------------------------------------ display -------------------------------------------------------
    void display() const override;

    // --------------------------------------------- comparisons ------------------------------------------------------
    bool operator<(const Movie *other) const override;
    bool operator==(const Movie *other) const override;

    // ------------------------------------------------ metadata ------------------------------------------------------
    char        getCategory() const override;
    std::string buildKey()    const override;

    // --------------------------------------------- accessors --------------------------------------------------------
    int         getReleaseMonth()   const;
    std::string getMajorActorFirst() const;
    std::string getMajorActorLast()  const;

private:
    int         releaseMonth;
    std::string majorActorFirst;
    std::string majorActorLast;
};

#endif // CLASSICS_H