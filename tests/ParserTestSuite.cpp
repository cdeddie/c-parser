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
            std::stringstream input = loadTestFile("/parser/while_loop.c");
            Lexer lexer(input);
            Parser parser(lexer);
            PrintVisitor visitor;
            auto ast = parser.parse();
            ast->printTree(visitor);
        });

        runTest("For loop test", [&]() {
            std::stringstream input = loadTestFile("/parser/for_loop.c");
            Lexer lexer(input);
            Parser parser(lexer);
            PrintVisitor visitor;
            auto ast = parser.parse();
            ast->printTree(visitor);
        });

        runTest("If statement test", [&]() {
            std::stringstream input = loadTestFile("/parser/if_else.c");
            Lexer lexer(input);
            Parser parser(lexer);
            PrintVisitor visitor;
            auto ast = parser.parse();
            ast->printTree(visitor);
        });
    }
};

int main()
{
    ParserTestSuite suite;
    suite.run();
}