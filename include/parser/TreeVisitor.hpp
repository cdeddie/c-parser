#pragma once

#include "parser/Visitor.hpp"

#include <string>

class TreeVisitor : public Visitor
{
public:

    // Base AST nodes
    virtual void visit(const BlockNode& node) const override;
    virtual void visit(const FunctionDefinitionNode& node) const override;
    virtual void visit(const IdentifierNode& node) const override;
    virtual void visit(const ParameterNode& node) const override;
    virtual void visit(const ProgramNode& node) const override;
    virtual void visit(const TypeNode& node) const override;

    // Expression nodes
    virtual void visit(const BinaryExpressionNode& node) const override;
    virtual void visit(const ExpressionNode& node) const override;
    virtual void visit(const FunctionCallExpressionNode& node) const override;
    virtual void visit(const UnaryExpressionNode& node) const override;
    virtual void visit(const VariableReferenceNode& node) const override;

    // Literal nodes (under Expression)
    virtual void visit(const CharLiteralNode& node) const override;
    virtual void visit(const FloatLiteralNode& node) const override;
    virtual void visit(const IntegerLiteralNode& node) const override;
    virtual void visit(const LiteralNode& node) const override;
    virtual void visit(const StringLiteralNode& node) const override;

    // Statement nodes
    virtual void visit(const ReturnNode& node) const override;
    virtual void visit(const StatementNode& node) const override;
    virtual void visit(const VariableDefinitionNode& node) const override;
    virtual void visit(const AssignmentStatementNode& node) const override;
    virtual void visit(const FunctionCallStatementNode& node) const override;
    virtual void visit(const ForNode& node) const override;
    virtual void visit(const IfNode& node) const override;
    virtual void visit(const WhileNode& node) const override;

    // Declaration nodes (under Statement)
    virtual void visit(const FunctionDeclarationNode& node) const override;
    virtual void visit(const VariableDeclarationNode& node) const override;

    virtual void visit(const ArraySpecifierNode& node) const override;
    virtual void visit(const ArrayInitializerNode& node) const override;
    std::string getJson() const;
private:
    mutable std::string json;
};