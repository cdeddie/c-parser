#pragma once

#include "parser/ParserIncludes.hpp"

// accept method needs to be pure virtual as the version of the method is
// determined by the dynamic type of the object, not the static type
// We are working with unique_ptrs

class Visitor
{
public:
    virtual ~Visitor() = default;

    // Base AST nodes
    virtual void visit(const BlockNode& node) const = 0;
    virtual void visit(const FunctionDefinitionNode& node) const = 0;
    virtual void visit(const VariableDefinitionNode& node) const = 0;
    virtual void visit(const IdentifierNode& node) const = 0;
    virtual void visit(const ParameterNode& node) const = 0;
    virtual void visit(const ProgramNode& node) const = 0;
    virtual void visit(const TypeNode& node) const = 0;

    // Expression nodes
    virtual void visit(const BinaryExpressionNode& node) const = 0;
    virtual void visit(const ExpressionNode& node) const = 0;
    virtual void visit(const FunctionCallNode& node) const = 0;
    virtual void visit(const UnaryExpressionNode& node) const = 0;
    virtual void visit(const VariableReferenceNode& node) const = 0;

    // Literal nodes (under Expression)
    virtual void visit(const CharLiteralNode& node) const = 0;
    virtual void visit(const FloatLiteralNode& node) const = 0;
    virtual void visit(const IntegerLiteralNode& node) const = 0;
    virtual void visit(const LiteralNode& node) const = 0;
    virtual void visit(const StringLiteralNode& node) const = 0;

    // Statement nodes
    virtual void visit(const ReturnNode& node) const = 0;
    virtual void visit(const StatementNode& node) const = 0;

    // Declaration nodes (under Statement)
    virtual void visit(const FunctionDeclarationNode& node) const = 0;
    virtual void visit(const VariableDeclarationNode& node) const = 0;
};