#pragma once

#include <string>
#include <istream>
#include "lexer/Token.hpp"

/* 
    Lexer that converts input string into a series of Tokens. 
    Constructor prevents implicit conversions

*/
class Lexer 
{
public:
    explicit Lexer(std::istream& input);

    Token nextToken();
    Token peekToken();
    char peekChar();
    
    std::streampos getPosition() const;
    void restorePosition(std::streampos pos);

private:
    std::istream& input;
    char currentChar;
    int currentLine;
    int currentColumn;
    void advance();

    Token identifier();
    Token number();
    Token stringLiteral();
    Token charLiteral();
    Token symbol();
    Token preprocessorDirective();
};