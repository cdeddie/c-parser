#include "parser/ParserIncludes.hpp"
#include "parser/PrintVisitor.hpp"

std::unique_ptr<FunctionDefinitionNode> buildASTTestOne();

int main()
{
    PrintVisitor printer;
    auto functionDefinition = buildASTTestOne();
    functionDefinition->accept(printer);

    return 0;
}

/*
//  int add(int x, int y)
//  {
//  	int z = x + y;
//  	return z;
//  }
*/

std::unique_ptr<FunctionDefinitionNode> buildASTTestOne()
{
    auto returnType = std::make_unique<TypeNode>("int");

    auto functionName = std::make_unique<IdentifierNode>("add");

    auto param1Type = std::make_unique<TypeNode>("int");
    auto param1Name = std::make_unique<IdentifierNode>("x");
    auto param1 = std::make_unique<ParameterNode>(std::move(param1Type), std::move(param1Name));

    auto param2Type = std::make_unique<TypeNode>("int");
    auto param2Name = std::make_unique<IdentifierNode>("y");
    auto param2 = std::make_unique<ParameterNode>(std::move(param2Type), std::move(param2Name));

    std::vector<std::unique_ptr<ParameterNode>> parameters;
    parameters.push_back(std::move(param1));
    parameters.push_back(std::move(param2));

    auto variableType = std::make_unique<TypeNode>("int");
    auto variableName = std::make_unique<IdentifierNode>("z");

    auto leftExpression = std::make_unique<VariableReferenceNode>(std::make_unique<IdentifierNode>("x"));
    auto rightExpression = std::make_unique<VariableReferenceNode>(std::make_unique<IdentifierNode>("y"));
    auto expression = std::make_unique<BinaryExpressionNode>(std::move(leftExpression), std::move(rightExpression), BinaryOperatorType::Plus);

    auto variableDeclaration = std::make_unique<VariableDefinitionNode>
        (std::move(variableType), std::move(variableName), std::move(expression));

    auto returnExpression = std::make_unique<VariableReferenceNode>(std::make_unique<IdentifierNode>("z"));
    auto returnNode = std::make_unique<ReturnNode>(std::move(returnExpression));

    std::vector<std::unique_ptr<StatementNode>> statements;
    statements.push_back(std::move(variableDeclaration));
    statements.push_back(std::move(returnNode));

    auto block = std::make_unique<BlockNode>(std::move(statements));

    auto functionDefinition = std::make_unique<FunctionDefinitionNode>
        (std::move(returnType), std::move(functionName), std::move(parameters), std::move(block));

    return functionDefinition;
}

/*
//  
//
//
//
//
//
*/