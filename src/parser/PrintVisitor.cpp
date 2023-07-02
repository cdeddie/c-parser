#include "parser/PrintVisitor.hpp"

#include <iostream>

PrintVisitor::PrintVisitor()
    : level(0)
{
}

PrintVisitor::~PrintVisitor()
{
}

void PrintVisitor::visit(const BlockNode& node) const
{
    printIndent();
    std::cout << "BlockNode: " << std::endl;
    for (const auto& statement : node.getStatements()) 
    {
        level++;
        statement->accept(*this);
        level--;
    }
}

void PrintVisitor::visit(const FunctionDefinitionNode& node) const
{
    printIndent();
    std::cout << "FunctionDefinitionNode: " << std::endl;;

    level++;
    node.getIdentifier().accept(*this);
    node.getReturnType().accept(*this);

    for (const auto& parameter : node.getParameters()) 
    {
        parameter->accept(*this);
    }

    node.getBlock().accept(*this);
    level--;

}

void PrintVisitor::visit(const IdentifierNode& node) const
{   
    printIndent();
    std::cout << "IdentifierNode: " << node.getName() << std::endl;
}

void PrintVisitor::visit(const ParameterNode& node) const
{
    printIndent();
    std::cout << "ParameterNode: " << std::endl;
    level++;
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);
    level--;
}

void PrintVisitor::visit(const ProgramNode& node) const
{
    // TODO: Implement ProgramNode visit
    printIndent();
    std::cout << "ProgramNode: " << std::endl;
}

void PrintVisitor::visit(const TypeNode& node) const
{
    printIndent();
    std::cout << "TypeNode: " << node.getType() << std::endl;
}

void PrintVisitor::visit(const BinaryExpressionNode& node) const
{
    printIndent();
    std::cout << "BinaryExpressionNode: " << std::endl;
    level++;
    // Virtual dispatch mechanism - calls correct visit function based on object type
    node.getLeft().accept(*this);
    std::cout << "Op: " << node.getOperator() << std::endl;
    node.getRight().accept(*this);
    level--;
}

void PrintVisitor::visit(const ExpressionNode& node) const
{
    // Empty parent class
    std::cout << "Unexpected ExpressionNode" << std::endl;
}

void PrintVisitor::visit(const FunctionCallNode& node) const
{
    printIndent();
    std::cout << "FunctionCallNode: " << std::endl;
    level++;
    node.getIdentifier().accept(*this);

    for (const auto& argument : node.getArguments()) 
    {
        argument->accept(*this);
    }
    level--;
}

void PrintVisitor::visit(const UnaryExpressionNode& node) const
{
    printIndent();
    std::cout << "UnaryExpressionNode: " << std::endl;
    level++;
    node.getOperand().accept(*this);
    std::cout << "Op: " << node.getOperator() << std::endl;
    level--;
}

void PrintVisitor::visit(const VariableReferenceNode& node) const
{
    printIndent();
    std::cout << "VariableReferenceNode: " << std::endl;
    level++;
    node.getIdentifier().accept(*this);
    level--;
}

void PrintVisitor::visit(const CharLiteralNode& node) const
{
    printIndent();
    std::cout << "CharLiteralNode: " << node.getValue() << std::endl;
}

void PrintVisitor::visit(const FloatLiteralNode& node) const
{
    printIndent();
    std::cout << "FloatLiteralNode: " << node.getValue() << std::endl;
}

void PrintVisitor::visit(const IntegerLiteralNode& node) const
{
    printIndent();
    std::cout << "IntegerLiteralNode: " << node.getValue() << std::endl;
}

void PrintVisitor::visit(const LiteralNode& node) const
{
    // Empty parent class
    std::cout << "Unexpected LiteralNode" << std::endl;
}

void PrintVisitor::visit(const StringLiteralNode& node) const
{
    printIndent();
    std::cout << "StringLiteralNode: " << node.getValue() << std::endl;
}

void PrintVisitor::visit(const ReturnNode& node) const
{
    printIndent();
    std::cout << "ReturnNode: " << std::endl;
    level++;
    node.getExpression().accept(*this);
    level--;
}

void PrintVisitor::visit(const StatementNode& node) const
{
    // Empty parent class
    std::cout << "Unexpected StatementNode" << std::endl;
}

void PrintVisitor::visit(const DeclarationNode& node) const
{
    // Inherited parent class
    std::cout << "Unexpected DeclarationNode" << std::endl;
}

void PrintVisitor::visit(const FunctionDeclarationNode& node) const
{
    printIndent();
    std::cout << "FunctionDeclarationNode: " << std::endl;
    level++;
    node.getIdentifier().accept(*this);
    node.getType().accept(*this);
    node.getExpression().accept(*this);
    level--;

}

void PrintVisitor::visit(const VariableDeclarationNode& node) const
{
    printIndent();
    std::cout << "VariableDeclarationNode: " << std::endl;
    level++;
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);
    node.getInit().accept(*this);
    level--;
}

void PrintVisitor::printIndent() const
{
    for (int i = 0; i < level - 1; i++) 
    {
        std::cout << "|   ";
    }
    if (level > 0)
    {
        std::cout << "+---";
    }
}