#include "lexer/Lexer.hpp"
#include <cctype>
#include <vector>
#include <algorithm>

Lexer::Lexer(std::istream& input) : input(input), currentChar(0), currentLine(1), currentColumn(0) 
{
    advance();
}

// Advances to the next character in the input stream
// get() does not skip whitespace
void Lexer::advance() 
{
    if (currentChar == '\n')
    {
        currentLine++;
        currentColumn = 0;
    }
    else
    {
        currentColumn++;
    }

    if (input)
        currentChar = input.get();
    else
        currentChar = '\0';
}

// Core of lexical analysis, analyses the currentChar
Token Lexer::nextToken() 
{
    while (currentChar != '\0') 
    {
        if (std::isspace(currentChar)) 
        {
            advance();
            continue;
        } 
        else if (std::isalpha(currentChar) || currentChar == '_') 
            return identifier();
        else if (std::isdigit(currentChar))
            return number();
        else if (currentChar == '"')
            return stringLiteral();
        else if (currentChar == '\'') 
            return charLiteral();
        else if (currentChar == '#')
            return preprocessorDirective();
        else 
            return symbol();

        advance();
    }
    return Token(TokenType::EndOfFile, "", currentLine, currentColumn);
}

// Stack overflow prevention for symbol ?
char Lexer::peekChar()
{
    char nextChar;
    if (input.peek() != EOF)
        nextChar = input.peek();
    else
        nextChar = '\0';
    return nextChar;
}

// 
Token Lexer::peekToken()
{
    std::streampos pos = getPosition();
    Token token = nextToken();
    restorePosition(pos);
    return token;
}

// Gets stream pos, maybe needed for 'undo' reading
std::streampos Lexer::getPosition() const
{
    return input.tellg();
}

void Lexer::restorePosition(std::streampos pos)
{
    input.seekg(pos);
    currentLine = 1; //Need to track line numbers
} 


Token Lexer::identifier()
{
    // While currentChar is alphanumeric
    std::string result;
    while (std::isalnum(currentChar) || currentChar == '_')
    {
        result.push_back(currentChar);
        advance();
    }

    // Check if the indentifier is a keyword or type
    static const std::vector<std::string> keywords = {"else", "for", "if", "while"};
    static const std::vector<std::string> types = {"char", "float", "int", "void"};

    if (result == "return")
        return Token(TokenType::Return, result, currentLine, currentColumn);
    else if (std::find(keywords.begin(), keywords.end(), result) != keywords.end())
        return Token(TokenType::Keyword, result, currentLine, currentColumn);
    else if (std::find(types.begin(), types.end(), result) != types.end())
        return Token(TokenType::Type, result, currentLine, currentColumn);
    else
        return Token(TokenType::Identifier, result, currentLine, currentColumn);
}

Token Lexer::number() 
{
    std::string result;
    bool isFloat = false;
    while (std::isdigit(currentChar) || currentChar == '.') 
    {
        if (currentChar == '.')
        {
            if (result.find('.') != std::string::npos)
            {
                return Token(TokenType::Error, result, currentLine, currentColumn);
            }
            isFloat = true;
        }
        result.push_back(currentChar);
        advance();
    }
    if (isFloat)
        return Token(TokenType::Float, result, currentLine, currentColumn);
    else 
        return Token(TokenType::Integer, result, currentLine, currentColumn);
}

// Loop checks that current is not a closing double quote or EOF, if no closing quote
// return Error Token
Token Lexer::stringLiteral()
{
    std::string result;
    result.push_back(currentChar);
    advance();

    while (currentChar != '"' && currentChar != '\0') 
    {
        result.push_back(currentChar);
        advance();
    }

    if (currentChar == '"') 
    {
        result.push_back(currentChar);
        advance();
        return Token(TokenType::StringLiteral, result, currentLine, currentColumn);
    } 
    else 
    {
        return Token(TokenType::Error, result, currentLine, currentColumn);
    }
}

// Same as stringLiteral, but checks for closing single quote. \'
Token Lexer::charLiteral() 
{
    std::string result;
    result.push_back(currentChar);
    advance();

    if (currentChar != '\'' && currentChar != '\0') 
    {
        result.push_back(currentChar);
        advance();
    }

    if (currentChar == '\'') 
    {
        result.push_back(currentChar);
        advance();
        return Token(TokenType::CharLiteral, result, currentLine, currentColumn);
    } else 
    {
        return Token(TokenType::Error, result, currentLine, currentColumn);
    }
}

Token Lexer::symbol() 
{
    if (currentChar == '\0')
        return Token(TokenType::EndOfFile, "", currentLine, currentColumn);
    
    std::string sym(1, currentChar);
    TokenType tokenType;

    switch (currentChar)
    {
    case '(':
        tokenType = TokenType::OpenParen;
        break;
    case ')':
        tokenType = TokenType::CloseParen;
        break;
    case '{':
        tokenType = TokenType::OpenBracket;
        break;
    case '}':
        tokenType = TokenType::CloseBracket;
        break;
    case ';':
        tokenType = TokenType::Semicolon;
        break;
    case ',':
        tokenType = TokenType::Comma;
        break;
    case '+':
        if (peekChar() == '+') {
            tokenType = TokenType::Increment;
            sym += "+";
            advance();
        } else {
            tokenType = TokenType::Plus;
        }
        break;
    case '-':
        if (peekChar() == '-') {
            tokenType = TokenType::Decrement;
            sym += "-";
            advance();
        } else {
            tokenType = TokenType::Minus;
        }
        break;
    case '!':
        tokenType = TokenType::Exclamation;
        break;
    case '&':
        tokenType = TokenType::Ampersand;
        break;
    case '*':
        tokenType = TokenType::Asterisk;
        break;
    default:
        tokenType = TokenType::Symbol;
        break;
    }

    advance();
    return Token(tokenType, sym, currentLine, currentColumn);
}

Token Lexer::preprocessorDirective()
{
    std::string result;
    while (currentChar != '\n' && currentChar != '\0')
    {
        result.push_back(currentChar);
        advance();
    }
    // Differentiate between #include, #define
    return Token(TokenType::PreprocessorDirective, result, currentLine, currentColumn);
}