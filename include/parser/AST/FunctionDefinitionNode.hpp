#pragma once

#include "parser/AST/BlockNode.hpp"
#include "parser/AST/ParameterNode.hpp"

class FunctionDefinitionNode : public Node
{
public:
    FunctionDefinitionNode(); // Sets all members to null
    FunctionDefinitionNode(
        std::unique_ptr<IdentifierNode> identifier,
        std::unique_ptr<TypeNode> returnType,
        std::vector<std::unique_ptr<ParameterNode>> parameters,
        std::unique_ptr<BlockNode> body,
        int line = 0,
        int column = 0
    );

    virtual void accept(const Visitor& visitor) const override;

    void setIdentifier(std::unique_ptr<IdentifierNode> identifier);
    void setReturnType(std::unique_ptr<TypeNode> returnType);
    void setParameters(std::vector<std::unique_ptr<ParameterNode>> parameters);
    void setBlock(std::unique_ptr<BlockNode> body);

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