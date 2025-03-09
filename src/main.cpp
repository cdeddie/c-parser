#include <iostream>
#include <sstream>
#include <string>
#include "parser/Parser.hpp"
#include "parser/PrintVisitor.hpp"
#include "analysis/Preprocessor.hpp"
#include "parser/TreeVisitor.hpp"

#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

std::string run_processing(const std::string& input)
{
    try
    {
        std::istringstream input_stream(input);
        std::string line, directivesCode, processedCode;
        int count = 0;
        const int MAX_LINES = 500;

        // Process input lines
        while (std::getline(input_stream, line)) {
            if (count >= MAX_LINES) {
                throw std::runtime_error("Input exceeds maximum allowed lines");
            }

            if (line.size() > 1000) {
                throw std::runtime_error("Input line exceeds maximum allowed length");
            }

            if (!line.empty() && line[0] == '#') {
                directivesCode += line + "\n";
            } else {
                processedCode += line + "\n";
            }
            count++;
        }

        // Process directives
        Preprocessor preprocessor(directivesCode);
        preprocessor.process();

        // Parse main code
        std::istringstream processed_stream(processedCode);
        Lexer lexer(processed_stream);
        Parser parser(lexer);
        auto ast = parser.parse();

        TreeVisitor TreeVisitor;
        ast->getRoot().accept(TreeVisitor);
        return TreeVisitor.getJson();
    }
    catch (const std::exception& e)
    {
        return std::string("Error: ", e.what());
    }
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("run_processing", &run_processing);
}

// int main()
// {
//     std::ostringstream input_buffer;
//     std::string line;

//     while (std::getline(std::cin, line)) {
//         input_buffer << line << "\n";
//     }

//     std::string result = run_processing(input_buffer.str());
//     std::cout << result << std::endl;

//     return 0;
// }