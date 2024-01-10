#pragma once

#include <string>
#include <istream>
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include "lexer/Token.hpp"

/* 
    Lexer that converts input string into a series of Tokens. 
    The lexer works in tandem with the parser, using the advance() function,
    however when the parser needs to lookahead, a deque is used to store tokens for 
    the lexer to catch up to the parser.


*/

class Lexer 
{
public:
    explicit Lexer(std::istream& input);
    bool isAtEnd() const;

    Token nextToken();
    Token peekToken();
    Token peekToken(int n);
    Token getNextToken(); // Helper function used in enqueueToken() and getTokenVector()
    int peekChar();

    int getCurrentLine() const;
    int getCurrentColumn() const;
    char getCurrentChar() const;

    void printNextTokens(int n);
    void printAllTokens();

    // Returns vector of Tokens, used for syntax analysis in code editor
    std::vector<Token> getTokenVector(std::istream& input);

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