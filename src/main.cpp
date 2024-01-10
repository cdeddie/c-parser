#include <iostream>
#include <string>
#include <sstream>
#include "parser/Parser.hpp"
#include "parser/JsonExportVisitor.hpp"
#include "parser/PrintVisitor.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./main <output_format>\n";
        std::cerr << "       output_format: 1 for JSON, 2 for plain text\n";
        return 1;
    }

    int choice = std::stoi(argv[1]);

    std::string line, code;
    while (std::getline(std::cin, line))
        code += line + "\n";

    std::istringstream input(code);

    Lexer lexer(input);
    Parser parser(lexer);
    auto ast = parser.parse();

    if (choice == 1)
    {
        JsonExportVisitor jsonVisitor;
        nlohmann::json astJson = ast->toJson();
        std::cout << astJson.dump(4);
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
