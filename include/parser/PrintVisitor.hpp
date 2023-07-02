#pragma once

#include "parser/Visitor.hpp"

class PrintVisitor : public Visitor
{
public:
    PrintVisitor();
    virtual ~PrintVisitor();

    // Base AST nodes
    void visit(const BlockNode& node) const override;
    void visit(const FunctionDefinitionNode& node) const override;
    void visit(const IdentifierNode& node) const override;
    void visit(const ParameterNode& node) const override;
    void visit(const ProgramNode& node) const override;
    void visit(const TypeNode& node) const override;

    // Expression nodes
    void visit(const BinaryExpressionNode& node) const override;
    void visit(const ExpressionNode& node) const override;
    void visit(const FunctionCallNode& node) const override;
    void visit(const UnaryExpressionNode& node) const override;
    void visit(const VariableReferenceNode& node) const override;

    // Literal nodes (under Expression)
    void visit(const CharLiteralNode& node) const override;
    void visit(const FloatLiteralNode& node) const override;
    void visit(const IntegerLiteralNode& node) const override;
    void visit(const LiteralNode& node) const override;
    void visit(const StringLiteralNode& node) const override;

    // Statement nodes
    void visit(const ReturnNode& node) const override;
    void visit(const StatementNode& node) const override;

    // Declaration nodes (under Statement)
    void visit(const DeclarationNode& node) const override;
    void visit(const FunctionDeclarationNode& node) const override;
    void visit(const VariableDeclarationNode& node) const override;
private:
    mutable int level;

    void printIndent() const;
};