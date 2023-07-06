#pragma once

#include <string>
#include <istream>
#include "lexer/Token.hpp"

/* 
    Lexer that converts input string into a series of Tokens. 
    Constructor prevents implicit conversions

*/

// Used for getting and restoring the position of the lexer
struct LexerPosition
{
    std::streampos pos;
    int line;
    int column;
};

class Lexer 
{
public:
    explicit Lexer(std::istream& input);
    bool isAtEnd() const;

    Token nextToken();
    Token peekToken();
    Token peekToken(int n);
    char peekChar();

    const int getCurrentLine() const;
    const int getCurrentColumn() const;
    
    LexerPosition getPosition() const;
    void restorePosition(LexerPosition lexerPos);

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