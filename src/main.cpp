#include <iostream>
#include <string>
#include <sstream>

#include "parser/Parser.hpp"
#include "parser/PrintVisitor.hpp"
#include "analysis/Preprocessor.hpp"
#include "parser/HTMLVisitor.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./main <output_format>\noutput_format: 1 for HTML, 2 for plaintext\n";
        return 1;
    } 

    int choice = std::stoi(argv[1]);
    if (choice != 1 && choice != 2)
    {
        std::cerr << "Invalid output format. Use 1 for HTML and 2 for plaintext\n";
        return 1;
    }

    std::string line, directivesCode, processedCode;
    int count = 0;
    const int MAX_LINES = 500;

    while (std::getline(std::cin, line)) {
        if (count >= MAX_LINES)
        {
            std::cerr << "Input exceeds maximum allowed lines\n";
            return 1;
        }

        if (line.size() > 1000)
        {
            std::cerr << "Input line exceeds maximum allowed length\n";
            return 1;
        }
        
        if (!line.empty() && line[0] == '#') {
            directivesCode += line + "\n";
        } else {
            processedCode += line + "\n";
        }
        count++;
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
