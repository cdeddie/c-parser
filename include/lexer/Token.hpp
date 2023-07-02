#pragma once
#include <string>

/* 
    Lexical token. Uses a TokenType enum class (strongly typed, scoped enums). 
    Contains two member variables - a TokenType type, and std::string value.
*/

enum class TokenType 
{
    Identifier,
    Keyword,
    Return,
    Type,
    Symbol,
    Integer,
    Float,
    StringLiteral,
    CharLiteral,
    Whitespace,
    Comment,
    Semicolon,
    OpenParen, CloseParen, 
    OpenBracket, CloseBracket,
    EndOfFile,
    Error,
    Comma,
    Plus, Minus, Exclamation,
    Increment, Decrement,
    Ampersand, Asterisk,
    PreprocessorDirective,
};

class Token 
{
public:
    Token(TokenType type, const std::string& value, int line, int column);
    Token();
    TokenType getType() const;
    const std::string& getValue() const; 

    int getLine() const;
    int getColumn() const;
    
private:
    TokenType type;
    std::string value;
    int line;
    int column;
};