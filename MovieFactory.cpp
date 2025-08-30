// ------------------------------------------- MovieFactory.cpp -------------------------------------------------------
// Programmer: <Clayton McArthur>   
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Implements enum-based creation of derived Movie objects. Returns nullptr with an error message for
//          unrecognized genres.
// --------------------------------------------------------------------------------------------------------------------

#include "MovieFactory.h"
#include "comedy.h"
#include "drama.h"
#include "classics.h"
#include <iostream>  // std::cerr for error reporting

// ------------------------------------------ createMovie(enum) -------------------------------------------------------
Movie* MovieFactory::createMovie(const MovieGenre genre)
{
    Movie *m = nullptr;

    switch (genre)
    {
        case COMEDY:
            m = new Comedy();
            break;

        case DRAMA:
            m = new Drama();
            break;

        case CLASSICS:
            m = new Classics();
            break;

        default:
            std::cerr << "ERROR: invalid MovieGenre in MovieFactory::createMovie" << std::endl;
            return nullptr;
    }

    return m;
} // end of createMovie(enum)
