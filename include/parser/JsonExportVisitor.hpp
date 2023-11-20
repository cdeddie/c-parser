#pragma once

#include "Visitor.hpp"
#include "../json.hpp"
#include "parser/AST.hpp"

using json = nlohmann::json;

class JsonExportVisitor : public Visitor
{
private:
    // result member holds the JSON object, updating it upon each visit
    // mutable because the methods are const
    mutable json result;

    // Helper to add child nodes to JSON, handles recursion
    template <typename T>
    json addChildNodes(const std::vector<std::unique_ptr<T>>& children) const;
public:
    // Entry point of JSON conversion
    json toJson(const ProgramNode& node);

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
};