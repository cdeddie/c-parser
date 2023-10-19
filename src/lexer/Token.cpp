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

std::string Token::typeToString() const {
    auto it = tokenTypeStrings.find(type);
    if (it != tokenTypeStrings.end())
        return it->second;
    else
        throw std::runtime_error("Unknown TokenType");
}

std::string Token::toString(TokenType type)
{
    auto it = tokenTypeStrings.find(type);
    if (it != tokenTypeStrings.end())
        return it->second;
    else
        throw std::runtime_error("Unknown TokenType");
}

const std::map<TokenType, std::string> Token::tokenTypeStrings = {
    { TokenType::Identifier, "Identifier" },
    { TokenType::Keyword, "Keyword" },
    { TokenType::Return, "Return" },
    { TokenType::Type, "Type" },
    { TokenType::Symbol, "Symbol" },
    { TokenType::Integer, "Integer" },
    { TokenType::Float, "Float" },
    { TokenType::StringLiteral, "StringLiteral" },
    { TokenType::CharLiteral, "CharLiteral" },
    { TokenType::Assignment, "Assignment" },
    { TokenType::Comment, "Comment" },
    { TokenType::EndOfFile, "EndOfFile" },
    { TokenType::Error, "Error" },
    { TokenType::Semicolon, "Semicolon" },
    { TokenType::OpenParen, "OpenParen" },
    { TokenType::CloseParen, "CloseParen" },
    { TokenType::OpenBracket, "OpenBracket" },
    { TokenType::CloseBracket, "CloseBracket" },
    { TokenType::OpenSquare, "OpenSquare" },
    { TokenType::CloseSquare, "CloseSquare" },
    { TokenType::Comma, "Comma" },
    { TokenType::Plus, "Plus" },
    { TokenType::Minus, "Minus" },
    { TokenType::Asterisk, "Asterisk" },
    { TokenType::Modulus, "Modulus" },
    { TokenType::ForwardSlash, "ForwardSlash" },
    { TokenType::Increment, "Increment" },
    { TokenType::Decrement, "Decrement" },
    { TokenType::Ampersand, "Ampersand" },
    { TokenType::Exclamation, "Exclamation" },
    { TokenType::Negation, "Negation" },
    { TokenType::And, "And" },
    { TokenType::Or, "Or" },
    { TokenType::Equals, "Equals" },
    { TokenType::NotEquals, "NotEquals" },
    { TokenType::LessThan, "LessThan" },
    { TokenType::GreaterThan, "GreaterThan" },
    { TokenType::LessThanOrEqual, "LessThanOrEqual" },
    { TokenType::GreaterThanOrEqual, "GreaterThanOrEqual" },
    { TokenType::PreprocessorDirective, "PreprocessorDirective" }
};