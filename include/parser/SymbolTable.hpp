#pragma once

#include <unordered_map>
#include <string>
#include <variant>
#include <vector>

/*
//  The symbol table is used throughout semantic analysis and code generation to keep track
//  of indentifiers (variable/function names), and associated attributes (types, scopes).
//  When an identifier is declared, a new entry is added to the table. When an identifier is
//  referenced, the compiler looks it up in the table. It also enforces scope rules and detects
//  redeclarations and undeclared identifiers. 
//
//  This will be generated through the visitor method, after the parser has created the AST.
*/


struct Parameter
{
    std::string type;
    std::string name;
};

struct FunctionSignature
{
    std::string returnType;
    std::vector<Parameter> parameters;
};

struct Symbol 
{
    std::string name;
    enum class SymbolType { Int, Float, Char, Function} type;
    // Potentially more attributes // Parser does not support bool right now
    // Value can take on different types - int, float, char, function signature
    std::variant<int, float, char, FunctionSignature> value; 
    int pointerLevel = 0;
};

class SymbolTable
{
public:
    SymbolTable() = default;
    ~SymbolTable() = default;

    void insert(const std::string& name, Symbol::SymbolType type);
    bool exists(const std::string& name) const;
    const Symbol& lookup(const std::string& name) const;

private:
    std::unordered_map<std::string, Symbol> table;
};