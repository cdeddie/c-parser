#include "parser/ParserException.hpp"

ParserException::ParserException(const std::string& message, TokenType expected, const Token& received)
    : message(message), expected(expected), received(received)
{
}

// Fix the usage of Token::toString() 
const char* ParserException::what() const throw()
{
    std::ostringstream oss;
    oss << message << " Expected: " << Token::toString(expected);
    oss << ". Received: " << Token::toString(received.getType());
    oss << " at line " << received.getLine();
    oss << " at column " << received.getColumn() << ".";
    whatMessage = oss.str();
    return whatMessage.c_str();
}

TokenType ParserException::getExpected() const
{
    return expected;
}

const Token& ParserException::getReceived() const
{
    return received;
}