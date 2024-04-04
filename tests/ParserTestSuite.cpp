#include "TestSuite.hpp"
#include "parser/Parser.hpp"
#include "lexer/Lexer.hpp"
#include "parser/PrintVisitor.hpp"

class ParserTestSuite : public TestSuite
{
protected:
    void runTests() override
    {
        runTest("While loop test", [&]() {
            std::stringstream input = loadTestFile("/parser_input/while_loop.c");
            parseAndPrintAST(input);
        });

        runTest("For loop test", [&]() {
            std::stringstream input = loadTestFile("/parser_input/for_loop.c");
            parseAndPrintAST(input);
        });

        runTest("If statement test", [&]() {
            std::stringstream input = loadTestFile("/parser_input/if_else.c");
            parseAndPrintAST(input);
        });

        runTest("Array test", [&]() {
            std::stringstream input = loadTestFile("/parser_input/array.c");
            parseAndPrintAST(input);
        });
    }

private:
    void parseAndPrintAST(std::stringstream& input)
    {
        Lexer lexer(input);
        Parser parser(lexer);
        PrintVisitor visitor;
        auto ast = parser.parseTest();
        ast->printTree(visitor);
    }
};

int main()
{
    ParserTestSuite suite;
    suite.run();
}