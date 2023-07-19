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
    printIndent();
    std::cout << "ProgramNode: " << std::endl;

    level++;
    for (const auto& statement : node.getStatements()) 
    { 
        statement->accept(*this);
    }
    level--;
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
    printIndent();
    std::cout << "Op: " << node.getBinaryOperatorString() << std::endl;
    node.getRight().accept(*this);
    level--;
}

void PrintVisitor::visit(const ExpressionNode& node) const
{
    // Empty parent class
    std::cout << "Unexpected ExpressionNode" << std::endl;
}

void PrintVisitor::visit(const FunctionCallExpressionNode& node) const
{
    printIndent();
    std::cout << "FunctionCallExpressionNode: " << std::endl;
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
    printIndent();
    std::cout << "Op: " << node.getUnaryOperatorString() << std::endl;
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

void PrintVisitor::visit(const FunctionDeclarationNode& node) const
{
    printIndent();
    std::cout << "FunctionDeclarationNode: " << std::endl;
    level++;
    node.getIdentifier().accept(*this);
    node.getReturnType().accept(*this);
    
    for (const auto& parameter : node.getParameters()) 
    {
        parameter->accept(*this);
    }
    level--;

}

void PrintVisitor::visit(const VariableDeclarationNode& node) const
{
    printIndent();
    std::cout << "VariableDeclarationNode: " << std::endl;
    level++;
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);
    level--;
}

void PrintVisitor::visit(const VariableDefinitionNode& node) const
{
    printIndent();
    std::cout << "VariableDefinitionNode: " << std::endl;
    level++;
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);
    node.getInit().accept(*this);
    level--;
}

void PrintVisitor::visit(const FunctionCallStatementNode& node) const
{
    printIndent();
    std::cout << "FunctionCallStatementNode: " << std::endl;
    level++;
    node.getIdentifier().accept(*this);

    for (const auto& argument : node.getArguments()) 
    {
        argument->accept(*this);
    }
    level--;
}

void PrintVisitor::visit(const ForNode& node) const
{
    printIndent();
    std::cout << "ForNode: " << std::endl;
    level++;
    node.getInit().accept(*this);
    node.getCondition().accept(*this);
    node.getIncrement().accept(*this);

    for (const auto& statement : node.getBody()) 
    {
        statement->accept(*this);
    }
    level--;
}

void PrintVisitor::visit(const IfNode& node) const
{
    printIndent();
    std::cout << "IfNode: " << std::endl;
    level++;

    printIndent();
    std::cout << "| Condition: |" << std::endl;
    node.getCondition().accept(*this);

    printIndent();
    std::cout << "| ThenBlock: |" << std::endl;
    node.getThenBlock().accept(*this);

    const auto& elseIfBlocks = node.getElseIfBlocks();
    for (const auto& elseIf : elseIfBlocks)
    {
        printIndent();
        std::cout << "| ElseIfNode: |" << std::endl;
        level++;

        printIndent();
        std::cout << "| Condition: |" << std::endl;
        level++;
        elseIf.first->accept(*this);
        level--;

        printIndent();
        std::cout << "| Block: |" << std::endl;
        level++;
        elseIf.second->accept(*this);
        level--;
    }

    const auto& elseBlock = node.getElseBlock();
    if (elseBlock)
    {
        printIndent();
        std::cout << "| ElseBlock: |" << std::endl;
        level++;
        elseBlock->accept(*this);
        level--;
    }
}

void PrintVisitor::visit(const WhileNode& node) const
{
    printIndent();
    std::cout << "WhileNode: " << std::endl;
    level++;
    node.getCondition().accept(*this);
    node.getBody().accept(*this);
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