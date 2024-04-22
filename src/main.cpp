#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

#include "parser/Parser.hpp"
#include "parser/PrintVisitor.hpp"
#include "analysis/Preprocessor.hpp"
#include "parser/HTMLVisitor.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./main <output_format>\n";
        std::cerr << "       output_format: 1 for HTML, 2 for plain text\n";
        return 1;
    }

    int choice = std::stoi(argv[1]);

    std::string line, directivesCode, processedCode;

    while (std::getline(std::cin, line)) {
        if (!line.empty() && line[0] == '#') {
            directivesCode += line + "\n";
        } else {
            processedCode += line + "\n";
        }
    }

    Preprocessor preprocessor(directivesCode);
    preprocessor.process();

    std::istringstream input(processedCode);

    Lexer lexer(input);
    Parser parser(lexer);
    auto ast = parser.parse();

    if (choice == 1) {
        HTMLVisitor htmlVisitor;
        ast->printHTML(htmlVisitor);
        std::string html = htmlVisitor.getHTML();

        std::vector<std::string> paths = preprocessor.getPaths();
        std::cout << "INCLUDES:";
        for (int i = 0; i < paths.size(); i++) {
            std::cout << paths[i];
            if (i < paths.size() - 1)
                std::cout << ",";
        }
        std::cout << "\n";

        std::unordered_map<std::string, std::string> macros = preprocessor.getMacros();
        std::cout << "MACROS:";
        int cunt = 0;
        for (const auto& pair : macros) {
            std::cout << pair.first << "=" << pair.second;
            if (cunt++ < macros.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << "\n";
        std::cout << "HTML_START\n";
        std::cout << html << std::endl;
    } else if (choice == 2) {
        std::vector<std::string> paths = preprocessor.getPaths();
        for (const auto& path : paths)
            std::cout << "Included file: " << path << std::endl;

        std::unordered_map<std::string, std::string> macros = preprocessor.getMacros();
        for (const auto& pair : macros)
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;

        PrintVisitor printVisitor;
        ast->printTree(printVisitor);
    }

    return 0;
}
