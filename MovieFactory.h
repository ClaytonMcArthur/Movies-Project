// ------------------------------------------- MovieFactory.h ---------------------------------------------------------
// Programmer: <Clayton McArthur>  
// Creation Date: <2025-08-15>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Factory for creating Movie-derived objects. Supports two styles:
//          1) Enum-based creation (COMEDY/DRAMA/CLASSICS).
//          2) (Optional) Registry-based creation by category char, using MovieParams.
// Notes  : Registry methods are declared here but can be unused if enum creation is sufficient.
// --------------------------------------------------------------------------------------------------------------------

#ifndef MOVIEFACTORY_H
#define MOVIEFACTORY_H

#include "movie.h"
#include "comedy.h"
#include "drama.h"
#include "classics.h"

#include <functional> // std::function for optional registry callbacks
#include <map>        // std::map for optional code->creator registry
#include <string>     // std::string fields in MovieParams

// Bundles parameters for potential registry-based creation.
struct MovieParams {
    std::string title;
    int         stock;
    std::string director;
    int         year;
    int         month;        // classics-only
    std::string majorActor;   // classics-only (full name)
};

enum MovieGenre {
    COMEDY,
    DRAMA,
    CLASSICS
};

class MovieFactory {
public:
    // --------------------------------------------- registerGenre ----------------------------------------------------
    // Description: Register a creator function for a given category code (e.g., 'F','D','C').
    // Note: Optional — only needed if using the registry path.
    static void registerGenre(char code,
        std::function<Movie*(const MovieParams&)> creator);

    // --------------------------------------------- createMovie (char) -----------------------------------------------
    // Description: Create via char code using the registered factory map.
    // Note: Optional — only needed if using the registry path.
    static Movie* createMovie(char code, const MovieParams &params);

    // --------------------------------------------- createMovie (enum) -----------------------------------------------
    // Description: Create via enum (simple switch). Implemented in MovieFactory.cpp.
    static Movie* createMovie(const MovieGenre genre);

private:
    static std::map<char, std::function<Movie*(const MovieParams&)>>& getRegistry();
};

#endif // MOVIEFACTORY_H
