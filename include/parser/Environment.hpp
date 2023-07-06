#pragma once

#include "parser/SymbolTable.hpp"
#include <stack>

class Environment
{
public:
    Environment() = default;
    ~Environment() = default;

    SymbolTable& getCurrentSymbolTable();
    void pushScope();
    void popScope();

    bool exists(const std::string& name) const;
    const Symbol& lookup(const std::string& name) const;

private:
    std::stack<SymbolTable> symbolTableStack;
};