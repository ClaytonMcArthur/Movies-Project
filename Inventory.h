// ------------------------------------------------- Inventory.h ------------------------------------------------------
// Programmer: <Marko Flores>  
// Creation Date: <2025-08-22>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose : Holds all movies, keyed by category and canonical key (see Movie::buildKey()).
//           Supports add/borrow/return and printing by required category order.
// --------------------------------------------------------------------------------------------------------------------

#ifndef INVENTORY_H
#define INVENTORY_H

#include "movie.h"   // base class interface for Movie hierarchy
#include <map>       // ordered category/key traversal
#include <string>    // std::string keys

class Inventory
{
public:
    Inventory() = default;
    ~Inventory();

    // ------------------------------------------------- addMovie -----------------------------------------------------
    // Description: Insert or merge stock for a movie. Ownership is taken on success.
    void addMovie(Movie* movie);

    // ------------------------------------------------ borrowMovie ---------------------------------------------------
    // Description: Decrement stock for a movie if available.
    // Returns    : true on success; false if not found or out of stock.
    bool borrowMovie(char category, const std::string &key, int year);

    // ------------------------------------------------ returnMovie ---------------------------------------------------
    // Description: Increment stock for a movie if it exists.
    // Returns    : true on success; false if the movie/key is unknown.
    bool returnMovie(char category, const std::string &key, int year);

    // ---------------------------------------------- displayInventory ------------------------------------------------
    // Description: Print inventory by category in assignment-specified format and order.
    void displayInventory() const;

    // ------------------------------------------------ loadMovies ----------------------------------------------------
    // Description: Load movies file; validates fields and merges duplicates by key.
    void loadMovies(const std::string &filename);

private:
    // category -> (key -> Movie*)
    std::map<char, std::map<std::string, Movie*>> inventoryMap;
};

#endif // INVENTORY_H