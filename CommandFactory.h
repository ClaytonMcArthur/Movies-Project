// --------------------------------------------- CommandFactory.h -----------------------------------------------------
// Programmer: <Clayton McArthur>     
// Creation Date: <2025-08-20>
// Last Modified: <2025-08-24>
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Factory/registry that maps the leading action code in a line ('I','H','B','R') to a parser function that
//          constructs a concrete Command.
// Notes  : - To add a new command, register its parser in ensureRegistered() in CommandFactory.cpp.
//          - Lines that fail to parse return nullptr and should be skipped by the caller.
// --------------------------------------------------------------------------------------------------------------------

#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "Command.h"
#include <functional>
#include <map>
#include <string>

class CommandFactory
{
public:
    // --------------------------------------------------------------------------------------------------------------
    // registerCommand
    // Description: Register a parser for a given action letter.
    // --------------------------------------------------------------------------------------------------------------
    static void registerCommand(char commandType,
                                std::function<Command*(const std::string&)> creator);

    // --------------------------------------------------------------------------------------------------------------
    // createCommand
    // Description: Choose the right parser based on the first char of the line, then parse it.
    // Returns    : New Command* (caller owns), or nullptr if line is invalid/unsupported.
    // --------------------------------------------------------------------------------------------------------------
    static Command* createCommand(const std::string &line);

private:
    static std::map<char, std::function<Command*(const std::string&)>>& getRegistry();
};

#endif // COMMANDFACTORY_H