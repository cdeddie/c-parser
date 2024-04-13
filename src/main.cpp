#include <iostream>
#include <string>
#include <sstream>
#include "parser/Parser.hpp"
#include "parser/JsonExportVisitor.hpp"
#include "parser/PrintVisitor.hpp"
#include "analysis/Preprocessor.hpp"
#include "parser/HTMLVisitor.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./main <output_format>\n";
        std::cerr << "       output_format: 1 for JSON, 2 for plain text\n";
        return 1;
    }

    int choice = std::stoi(argv[1]);

    std::string line, directivesCode, processedCode;

    while (std::getline(std::cin, line))
    {
        if (!line.empty() && line[0] == '#')
        {
            directivesCode += line + "\n";
        }
        else
        {
            processedCode += line + "\n";
        }
    }

    Preprocessor preprocessor(directivesCode);
    preprocessor.process();

    std::unordered_map<std::string, std::string> macros = preprocessor.getMacros();
    for (const auto& pair : macros) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    std::istringstream input(processedCode);

    Lexer lexer(input);
    Parser parser(lexer);
    auto ast = parser.parse();

    if (choice == 1)
    {
        HTMLVisitor htmlVisitor;
        ast->printHTML(htmlVisitor);
        std::string html = htmlVisitor.getHTML();
        std::cout << html << std::endl;
    }
    else if (choice == 2)
    {
        PrintVisitor printVisitor;
        ast->printTree(printVisitor);
    }
    else
    {
        std::cerr << "Invalid output format!" << std::endl;
        return 1;
    }

    return 0;
}
