#include "parser/SymbolTable.hpp"

#include <stdexcept>

void SymbolTable::insert(const std::string& name, Symbol::SymbolType type) 
{
    // Check if the symbol already exists in the table
    if (table.find(name) != table.end()) 
	{
        throw std::runtime_error("Symbol already exists: " + name);
    }

    Symbol symbol = {name, type};
    table[name] = symbol;
}

bool SymbolTable::exists(const std::string& name) const 
{
    return table.find(name) != table.end();
}

const Symbol& SymbolTable::lookup(const std::string& name) const 
{
    if (!exists(name)) 
	{
        throw std::runtime_error("Symbol does not exist: " + name);
    }

    return table.at(name);
}
