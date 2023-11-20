#include "TestSuite.hpp"
#include "parser/Parser.hpp"
#include "lexer/Lexer.hpp"
#include "parser/JsonExportVisitor.hpp"
#include <iostream>
#include <fstream>

class JSONTestSuite : public TestSuite
{
protected:
    void runTests() override
    {
        runTest("While loop test", [&]() {
            std::stringstream input = loadTestFile("/JSON/input/basic.c");
            parseAndOutputJSON(input);
        });

        runTest("For loop test", [&]() {
            std::stringstream input = loadTestFile("/JSON/input/hello.c");
            parseAndOutputJSON(input);
        });
    }

private:
    void parseAndOutputJSON(std::stringstream& input) {
        Lexer lexer(input);
        Parser parser(lexer);
        JsonExportVisitor jsonVisitor;
        auto ast = parser.parse();
        
        json astJson = ast->toJson();

        std::cout << astJson.dump(2) << std::endl;
    }
};

int main() {
    JSONTestSuite suite;
    suite.run();
}
