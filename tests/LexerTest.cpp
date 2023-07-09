#include "lexer/Lexer.hpp"
#include "lexer/Token.hpp"
#include "parser/Parser.hpp"
#include "parser/PrintVisitor.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

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

    std::stringstream fileStream;
    fileStream << inputFile.rdbuf();
    inputFile.close();
    std::string fileContent = fileStream.str();

    Lexer lexer(fileStream);
    Parser parser(lexer);
    parser.printTokens(10);

    std::cout << "-------- Parser --------\n";
    // PARSER TEST - NEED TO WRITE OWN FILE OR TEST SUITE
    std::cout << "Beginning parse...\n";
    std::unique_ptr<AST> AST = parser.parse();

    std::cout << "\nParser output: \n";
    PrintVisitor printVisitor;
    AST->printTree(printVisitor);

    std::cout << "Success!\n";
}

int main() 
{
    handleFile();
    return 0;
}