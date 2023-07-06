#include "lexer/Lexer.hpp"
#include "lexer/Token.hpp"
#include "parser/Parser.hpp"
#include "parser/PrintVisitor.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

std::string getTokenTypeString(TokenType type);

void printTokens(const std::vector<Token>& tokens) 
{
    for (const auto& token : tokens) 
    {
        std::cout << getTokenTypeString(token.getType());
        if(token.getType() != TokenType::EndOfFile)
        {
            std::cout << "[ " << token.getValue() << " ]";
        }
        std::cout << " (line: " << token.getLine() 
                  << ", column: " << token.getColumn() << ")" << std::endl;
    }
}

void handleFile()
{
    std::cout << "== Test: C Source File ===" << std::endl;
    std::string currentFile(__FILE__);
    std::string basePath = currentFile.substr(0, currentFile.find_last_of("/\\"));
    std::string fileName = "/test.c";
    std::string filePath = basePath + fileName;

    std::ifstream inputFile1(filePath);
    if (!inputFile1.is_open())
    {
        std::cout << "Failed to open file: " << fileName << std::endl;
        return;
    }

    std::ifstream inputFile2(filePath);
    if (!inputFile2.is_open())
    {
        std::cout << "Failed to open file: " << fileName << std::endl;
        return;
    }

    Lexer lexer1(inputFile1);
        std::vector<Token> tokens;
    Token token;
    while ((token = lexer1.nextToken()).getType() != TokenType::EndOfFile) 
    {
        tokens.push_back(token);
    }

    // Print Lexer output
    std::cout << "Input (from file: " << fileName << "):" << std::endl;
    std::string line;
    while (std::getline(inputFile1, line))
    {
        std::cout << line << std::endl;
    }

    std::cout << "Lexer Output:" << std::endl;
    printTokens(tokens);

    // PARSER TEST - NEED TO WRITE OWN FILE OR TEST SUITE
    Lexer lexer2(inputFile2);
    Parser parser(lexer2);
    auto AST = parser.parse();

    std::cout << "\nParser output: " << std::endl;
    PrintVisitor visitor;
    AST->printTree(visitor);
}

int main() 
{
    handleFile();
    return 0;
}

std::string getTokenTypeString(TokenType type) 
{
    static const std::map<TokenType, std::string> tokenTypeStrings = {
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
        { TokenType::Whitespace, "Whitespace" },
        { TokenType::Comment, "Comment" },
        { TokenType::EndOfFile, "EndOfFile" },
        { TokenType::Error, "Error" },
        { TokenType::Semicolon, "Semicolon" },
        { TokenType::OpenParen, "OpenParen" },
        { TokenType::CloseParen, "CloseParen" },
        { TokenType::OpenBracket, "OpenBracket" },
        { TokenType::CloseBracket, "CloseBracket" },
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
    
    auto it = tokenTypeStrings.find(type);
    if (it != tokenTypeStrings.end()) 
        return it->second;
    else 
        return "Unknown";
    
}