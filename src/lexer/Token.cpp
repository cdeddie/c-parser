#include "lexer/Token.hpp"

Token::Token(TokenType type, const std::string& value, int line, int column) 
    : type(type), value(value), line(line), column(column)
{

}

Token::Token() : type(TokenType::Error), value("") 
{

}

TokenType Token::getType() const 
{
    return type;
}

const std::string& Token::getValue() const 
{
    return value;
}

int Token::getLine() const
{
    return line;
}

int Token::getColumn() const 
{
    return column;
}
