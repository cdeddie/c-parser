#include <iostream>
#include <string>
#include "parser/Parser.hpp"
#include "parser/JsonExportVisitor.hpp"

int main()
{
    std::string line, code;
    while (std::getline(std::cin, line))
        code += line + "\n";

    std::istringstream input(code);

    Lexer lexer(input);
    Parser parser(lexer);
    JsonExportVisitor jsonVisitor;
    auto ast = parser.parse();

    nholmann:json astJson = ast->toJson();

    std::cout << astJson.dump(4);

}