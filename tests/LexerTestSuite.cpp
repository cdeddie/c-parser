#include "TestSuite.hpp"
#include "lexer/Lexer.hpp"

class LexerTestSuite : public TestSuite
{
protected:
    void runTests() override
    {
        runTest("Basic c program", [&]{
            std::stringstream input = loadTestFile("/lexer/basic.c");
            Lexer lexer(input);
            lexer.printAllTokens();
        });

        runTest("Functional c program", [&]{
            std::stringstream input = loadTestFile("/lexer/function.c");
            Lexer lexer(input);
            lexer.printAllTokens();
        });

        runTest("Control flow c program", [&]{
            std::stringstream input = loadTestFile("/lexer/control.c");
            Lexer lexer(input);
            lexer.printAllTokens();
        });
    }
};

int main()
{
    LexerTestSuite suite;
    suite.run();
}