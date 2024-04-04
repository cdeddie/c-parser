#include "lexer/Lexer.hpp"
#include <cctype>

Lexer::Lexer(std::istream& input) : input(input), currentChar(0), currentLine(1), currentColumn(0) 
{
    advance();
    enqueueToken();
}

// true if EOF, false otherwise
bool Lexer::isAtEnd() const
{
    return currentChar == EOF;
}

char Lexer::getCurrentChar() const
{
    return currentChar;
}

// Advances to the next character in the input stream
// get() does not skip whitespace
void Lexer::advance() 
{
    if (currentChar == EOF)
    {
        return;
    }

    if (currentChar == '\n')
    {
        currentLine++;
        currentColumn = 1;
    }
    else
    {
        currentColumn++;
    }

    if (input)
        currentChar = input.get();
    else
        currentChar = EOF;
}

Token Lexer::getNextToken() 
{
    if (currentChar == EOF)
        return Token(TokenType::EndOfFile, "", currentLine, currentColumn);

    if (std::isspace(currentChar)) 
    {
        advance();
        return getNextToken();  // Recursive call to skip whitespace and get the next token
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
}


Token Lexer::nextToken() 
{
    Token token = tokenQueue.front();
    tokenQueue.pop_front();
    enqueueToken();
    return token;
}

// Core of lexical analysis, analyses the currentChar
void Lexer::enqueueToken()
{
    Token next = getNextToken();
    tokenQueue.push_back(next);
}

std::vector<Token> Lexer::getTokenVector(std::istream& input)
{
    std::vector<Token> tokens;

    // Reset internal state (in case)
    currentChar = 0;
    currentLine = 1;
    currentColumn = 0;
    advance();

    Token nextToken;
    do 
    {
        nextToken = getNextToken();
        tokens.push_back(nextToken);
    } while (nextToken.getType() != TokenType::EndOfFile);    

    return tokens;
}

void Lexer::printAllTokens()
{
    while (!isAtEnd())
    {
        Token token = nextToken();
        std::cout << "Token: " << std::setw(30) << token.typeToString() << 
                    " (line " << token.getLine() << ", column " << token.getColumn() << ")\t\t | Value:" << token.getValue() << "\n";
    }
}

void Lexer::printNextTokens(int n)
{
    if (tokenQueue.empty())
    {
        std::cout << "No tokens available.\n";
        return;
    }
    
    std::cout << "Current Token: " << tokenQueue[0].typeToString() << 
                " (line " << tokenQueue[0].getLine() << ", column " << tokenQueue[0].getColumn() << ")\n";
                
    if (n < 1)
    {
        return;
    }
    
    while (tokenQueue.size() <= n)
    {
        enqueueToken();
    }
    
    for (int i = 1; i <= n; i++)
    {
        std::cout << "Token " << i << ": " << tokenQueue[i].typeToString() << 
                    " (line " << tokenQueue[i].getLine() << ", column " << tokenQueue[i].getColumn() << ")\n";
    }
}

// Stack overflow prevention for symbol ?
int Lexer::peekChar()
{
    int nextChar;
    if (input.peek() != EOF)
        nextChar = input.peek();
    else
        nextChar = EOF;
    return nextChar;
}

// 
Token Lexer::peekToken()
{
    return tokenQueue.front();
}

Token Lexer::peekToken(int n)
{
    while (tokenQueue.size() < n)
    {
        enqueueToken();
    }
    return tokenQueue[n - 1];
}

int Lexer::getCurrentLine() const
{
    return currentLine;
}

int Lexer::getCurrentColumn() const
{
    return currentColumn;
}

Token Lexer::identifier()
{
    // While currentChar is alphanumeric
    std::string result;

    int line = currentLine;
    int column = currentColumn;
    while (std::isalnum(currentChar) || currentChar == '_')
    {
        result.push_back(currentChar);
        advance();
    }

    // Check if the indentifier is a keyword or type
    static const std::vector<std::string> keywords = {"if", "else", "for","while"};
    static const std::vector<std::string> types = {"char", "float", "int", "void"};

    if (result == "return")
        return Token(TokenType::Return, result, line, column);
    else if (std::find(keywords.begin(), keywords.end(), result) != keywords.end())
        return Token(TokenType::Keyword, result, line, column);
    else if (std::find(types.begin(), types.end(), result) != types.end())
        return Token(TokenType::Type, result, line, column);
    else
        return Token(TokenType::Identifier, result, line, column);
}

Token Lexer::number() 
{
    std::string result;
    int line = currentLine;
    int column = currentColumn;
    bool isFloat = false;
    while (std::isdigit(currentChar) || currentChar == '.') 
    {
        if (currentChar == '.')
        {
            if (result.find('.') != std::string::npos)
            {
                return Token(TokenType::Error, result, line, column);
            }
            isFloat = true;
        }
        result.push_back(currentChar);
        advance();
    }
    if (isFloat)
        return Token(TokenType::Float, result, line, column);
    else 
        return Token(TokenType::Integer, result, line, column);
}

// Loop checks that current is not a closing double quote or EOF, if no closing quote
// return Error Token
Token Lexer::stringLiteral()
{
    std::string result;
    int line = currentLine;
    int column = currentColumn;
    result.push_back(currentChar);
    advance();

    while (currentChar != '"' && currentChar != EOF) 
    {
        result.push_back(currentChar);
        advance();
    }

    if (currentChar == '"') 
    {
        result.push_back(currentChar);
        advance();
        return Token(TokenType::StringLiteral, result, line, column);
    } 
    else 
    {
        return Token(TokenType::Error, result, line, column);
    }
}

// Same as stringLiteral, but checks for closing single quote. \'
Token Lexer::charLiteral() 
{
    std::string result;
    int line = currentLine;
    int column = currentColumn;
    result.push_back(currentChar);
    advance();

    if (currentChar != '\'' && currentChar != EOF) 
    {
        result.push_back(currentChar);
        advance();
    }

    if (currentChar == '\'') 
    {
        result.push_back(currentChar);
        advance();
        return Token(TokenType::CharLiteral, result, line, column);
    } else 
    {
        return Token(TokenType::Error, result, line, column);
    }
}

Token Lexer::symbol() 
{
    if (currentChar == EOF)
        return Token(TokenType::EndOfFile, "", currentLine, currentColumn);
    
    int line = currentLine;
    int column = currentColumn;

    std::string sym(1, static_cast<char>(currentChar));
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
    case '[':
        tokenType = TokenType::OpenSquare;
        break;
    case ']':
        tokenType = TokenType::CloseSquare;
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
        if (peekChar() == '=') {
            tokenType = TokenType::NotEquals;
            sym += "=";
            advance();
        } else {
            tokenType = TokenType::Exclamation;
        }
        break;
    case '&':
        if (peekChar() == '&') {
            tokenType = TokenType::And;
            sym += "&";
            advance();
        } else {
            tokenType = TokenType::Ampersand;
        }
        break;
    case '*':
        tokenType = TokenType::Asterisk;
        break;
    case '/':
        tokenType = TokenType::ForwardSlash;
        break;
    case '%':
        tokenType = TokenType::Modulus;
        break;
    case '=':
        if (peekChar() == '=') {
            tokenType = TokenType::Equals;
            sym += "=";
            advance();
        } else {
            tokenType = TokenType::Assignment;
        }
        break;
    case '>':
        if (peekChar() == '=') {
            tokenType = TokenType::GreaterThanOrEqual;
            sym += "=";
            advance();
        } else {
            tokenType = TokenType::GreaterThan;
        }
        break;
    case '<':
        if (peekChar() == '=') {
            tokenType = TokenType::LessThanOrEqual;
            sym += "=";
            advance();
        } else {
            tokenType = TokenType::LessThan;
        }
        break;
    case '|':
        if (peekChar() == '|') {
            tokenType = TokenType::Or;
            sym += "|";
            advance();
        }
        break;
    default:
        tokenType = TokenType::Symbol;
        break;
    }

    Token token = Token(tokenType, sym, line, column);
    advance();
    return token;
}

Token Lexer::preprocessorDirective()
{
    std::string result;
    int line = currentLine;
    int column = currentColumn;
    while (currentChar != '\n' && currentChar != EOF)
    {
        result.push_back(currentChar);
        advance();
    }
    // Differentiate between #include, #define
    return Token(TokenType::PreprocessorDirective, result, line, column);
}