#pragma once
#include <string>
#include <map>
#include <stdexcept>

/* 
//  Lexical token. Uses a TokenType enum class (strongly typed, scoped enums). 
//  Contains two member variables - a TokenType type, and std::string value.
//  !! c++ compiler catches errors at compile time rather than runtime, because
//  the c++ type system enforces correct usage of TokenTypes (ie compared to strings)
*/

enum class TokenType 
{
    Identifier, Keyword, Return, Type, Symbol,
    Integer, Float, StringLiteral, CharLiteral,
    Assignment, Whitespace, Comment, Semicolon,
    OpenParen, CloseParen, OpenBracket, CloseBracket,
    EndOfFile, Error, Comma,
    Plus, Minus, Asterisk, Modulus, ForwardSlash,
    Increment, Decrement,
    Ampersand, Exclamation,
    Negation, And, Or,
    Equals, NotEquals, LessThan, GreaterThan,
    LessThanOrEqual, GreaterThanOrEqual,
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

    std::string typeToString() const;
    static std::string toString(TokenType type);
private:
    TokenType type;
    std::string value;
    int line;
    int column;

    static const std::map<TokenType, std::string> tokenTypeStrings;
};