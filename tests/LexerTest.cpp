#include "lexer/Lexer.hpp"
#include "lexer/Token.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

std::string getTokenTypeString(TokenType type) 
{
    static const std::map<TokenType, std::string> tokenTypeStrings = {
        { TokenType::Identifier, "Identifier" },
        { TokenType::Keyword, "Keyword" },
        { TokenType::Return, "Return" },
        { TokenType::Symbol, "Symbol" },
        { TokenType::Type, "Type"},
        { TokenType::Integer, "Integer" },
        { TokenType::Float, "Float" },
        { TokenType::StringLiteral, "StringLiteral" },
        { TokenType::CharLiteral, "CharLiteral" },
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
        { TokenType::Exclamation, "Exclamation" },
        { TokenType::Increment, "Increment" },
        { TokenType::Decrement, "Decrement" },
        { TokenType::Ampersand, "Ampersand" },
        { TokenType::Asterisk, "Asterisk" },
        { TokenType::PreprocessorDirective, "PreprocessorDirective" }
    };
    
    auto it = tokenTypeStrings.find(type);
    if (it != tokenTypeStrings.end()) 
        return it->second;
    else 
        return "Unknown";
    
}

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

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open file: " << fileName << std::endl;
        return;
    }

    Lexer lexer(inputFile);
    std::vector<Token> tokens;
    Token token;
    while ((token = lexer.nextToken()).getType() != TokenType::EndOfFile) 
    {
        tokens.push_back(token);
    }

    std::cout << "Input (from file: " << fileName << "): " << std::endl;
    std::string line;
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    while (std::getline(inputFile, line))
    {
        std::cout << line << '\n';
    }
    inputFile.close();

    std::cout << "Output:" << std::endl;
    printTokens(tokens);
}

void handleOneLiner() 
{
    std::cout << "==== Test: HandleOneLiner ====" << std::endl;
    std::stringstream input("int x = 42;");
    Lexer lexer(input);

    std::vector<Token> tokens;
    Token token;
    while ((token = lexer.nextToken()).getType() != TokenType::EndOfFile) 
    {
        tokens.push_back(token);
    }

    std::cout << "Input: int x = 42;" << std::endl;
    std::cout << "Output:" << std::endl;
    printTokens(tokens);
}

void handleSimpleProgram() 
{
    std::cout << "==== Test: HandleSimpleProgram ====" << std::endl;
    std::stringstream input(R"(
        #include <stdio.h>

        int main() {
            float x = 5.5;
            printf("%d", x);
            printf("Hello world!");
            return 0;
        }
    )");
    Lexer lexer(input);

    std::vector<Token> tokens;
    Token token;
    while ((token = lexer.nextToken()).getType() != TokenType::EndOfFile) 
    {
        tokens.push_back(token);
    }

    std::cout << "Input: " << std::endl;
    std::cout << input.str() << std::endl;
    std::cout << "Output:" << std::endl;
    printTokens(tokens);
}

void handleComplexProgram() 
{
    std::cout << "==== Test: HandleComplexProgram ====" << std::endl;
    std::stringstream input(R"(
        #include <stdio.h>

        int add(int a, int b) {
            return a + b;
        }

        int main() {
            int x = 10;
            int y = 20;
            int sum = add(x, y);
            printf("Sum: %d\n", sum);
            return 0;
        }
    )");
    Lexer lexer(input);

    std::vector<Token> tokens;
    Token token;
    while ((token = lexer.nextToken()).getType() != TokenType::EndOfFile) 
    {
        tokens.push_back(token);
    }

    std::cout << "Input: " << std::endl;
    std::cout << R"(
        #include <stdio.h>

        int add(int a, int b) {
            return a + b;
        }

        int main() {
            int x = 10;
            int y = 20;
            int sum = add(x, y);
            printf("Sum: %d\n", sum);
            return 0;
        }
    )" << std::endl;
    std::cout << "Output:" << std::endl;
    printTokens(tokens);
}

int main() 
{
    handleFile();
    return 0;
}