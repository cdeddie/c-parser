#pragma once

#include <string>
#include <istream>
#include <iostream>
#include <deque>
#include "lexer/Token.hpp"

/* 
    Lexer that converts input string into a series of Tokens. 
    Constructor prevents implicit conversions

*/

class Lexer 
{
public:
    explicit Lexer(std::istream& input);
    bool isAtEnd() const;

    Token nextToken();
    Token peekToken();
    Token peekToken(int n);
    int peekChar();

    int getCurrentLine() const;
    int getCurrentColumn() const;
    char getCurrentChar() const;

    void printNextTokens(int n);
    void printAllTokens();

private:
    std::istream& input;
    std::deque<Token> tokenQueue;

    int currentChar;
    int currentLine;
    int currentColumn;

    void enqueueToken();
    void advance();

    Token identifier();
    Token number();
    Token stringLiteral();
    Token charLiteral();
    Token symbol();
    Token preprocessorDirective();
};