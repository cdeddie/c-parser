#pragma once

#include "parser/AST/BlockNode.hpp"
#include "parser/AST/ParameterNode.hpp"
#include "parser/AST/statement/StatementNode.hpp"

class FunctionDefinitionNode : public StatementNode
{
public:
    FunctionDefinitionNode(
        std::unique_ptr<TypeNode> returnType,
        std::unique_ptr<IdentifierNode> identifier,
        std::vector<std::unique_ptr<ParameterNode>> parameters,
        std::unique_ptr<BlockNode> body,
        int line = 0,
        int column = 0
    );

    virtual void accept(const Visitor& visitor) const override;

    const IdentifierNode& getIdentifier() const;
    const TypeNode& getReturnType() const;
    const std::vector<std::unique_ptr<ParameterNode>>& getParameters() const;
    const BlockNode& getBlock() const;

private:
    std::unique_ptr<BlockNode> body;
    std::vector<std::unique_ptr<ParameterNode>> parameters;
    std::unique_ptr<IdentifierNode> identifier;
    std::unique_ptr<TypeNode> returnType;
};

// TODO: figure out what to do with returnType (SymbolTable.hpp)