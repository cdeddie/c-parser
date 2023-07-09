#pragma once

#include <exception>
#include <sstream>
#include "lexer/Token.hpp"

class ParserException : public std::exception 
{
public:
    ParserException(const std::string& message, TokenType expected, const Token& received);
    const char* what() const throw();

    TokenType getExpected() const;
    const Token& getReceived() const;

private:
    std::string message;
    TokenType expected;
    Token received;
    mutable std::string whatMessage; // allows modification in what() const
};