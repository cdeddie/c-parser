#include "TestSuite.hpp"
#include "parser/Parser.hpp"
#include "lexer/Lexer.hpp"
#include "parser/PrintVisitor.hpp"

class PointerTestSuite : public TestSuite
{
protected:
    void runTests() override
    {
        runTest("Basic Pointer Declarations", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/basic_pointer_declarations.c");
            parseAndPrintAST(input);
        });

        runTest("Pointer to Pointer", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/pointer_to_pointer.c");
            parseAndPrintAST(input);
        });

        runTest("Pointer Initializations", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/pointer_initializations.c");
            parseAndPrintAST(input);
        });

        runTest("Array of Pointers", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/array_of_pointers.c");
            parseAndPrintAST(input);
        });

        runTest("Pointer Arithmetic", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/pointer_arithmetic.c");
            parseAndPrintAST(input);
        });

        runTest("Dereferencing", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/dereferencing.c");
            parseAndPrintAST(input);
        });

        runTest("Pointer Comparisons", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/pointer_comparisons.c");
            parseAndPrintAST(input);
        });

        runTest("Returning Pointer from a Function", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/return_pointer.c");
            Lexer lexer(input);
            Parser parser(lexer);
            PrintVisitor visitor;
            auto ast = parser.parse();
            ast->printTree(visitor);
        });

        runTest("Passing Pointer to a Function", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/pass_pointer.c");
            Lexer lexer(input);
            Parser parser(lexer);
            PrintVisitor visitor;
            auto ast = parser.parse();
            ast->printTree(visitor);
        });

        runTest("Dereferencing NULL Pointers", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/dereference_null.c");
            parseAndPrintAST(input);
        });

        runTest("Void Pointers", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/void_pointers.c");
            parseAndPrintAST(input);
        });

        runTest("Complex Dereferencing", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/complex_dereferencing.c");
            parseAndPrintAST(input);
        });

        runTest("Using Pointers in Expressions", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/pointers_in_expressions.c");
            parseAndPrintAST(input);
        });

        runTest("Misuse of & and * Operators", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/misuse_of_operators.c");
            parseAndPrintAST(input);
        });

        runTest("Pointer and Arrays", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/pointer_and_arrays.c");
            parseAndPrintAST(input);
        });

        runTest("Dereferencing Uninitialized Pointers", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/dereference_uninitialized.c");
            parseAndPrintAST(input);
        });

        runTest("Complex Declarations", [&]() {
            std::stringstream input = loadTestFile("/parser/pointers/complex_declarations.c");
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
    PointerTestSuite suite;
    suite.run();
}