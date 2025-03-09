#include "parser/Environment.hpp"

#include <stdexcept>

SymbolTable& Environment::getCurrentSymbolTable()
{
    return symbolTableStack.top();
}

void Environment::pushScope()
{
    symbolTableStack.emplace();
}

void Environment::popScope()
{
    symbolTableStack.pop();
}

bool Environment::exists(const std::string& name) const
{
    for (int i = symbolTableStack.size() - 1; i >= 0; i--)
    {
        if (symbolTableStack.top().exists(name))
        {
            return true;
        }
    }
    return false;
}

const Symbol& Environment::lookup(const std::string& name) const
{
    for (int i = symbolTableStack.size() - 1; i >= 0; i--)
    {
        if (symbolTableStack.top().exists(name))
        {
            return symbolTableStack.top().lookup(name);
        }
    }
    throw std::runtime_error("Symbol does not exist: " + name);
}