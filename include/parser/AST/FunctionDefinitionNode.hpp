#pragma once

#include "parser/AST/statement/StatementNode.hpp"
#include "parser/AST/BlockNode.hpp"
#include "parser/AST/TypeNode.hpp"
#include "parser/AST/IdentifierNode.hpp"
#include "parser/AST/ParameterNode.hpp"
#include <string>

class FunctionDefinitionNode : public Node
{
public:
    FunctionDefinitionNode(); // Sets all members to null
    FunctionDefinitionNode(
        std::unique_ptr<IdentifierNode> identifier,
        std::unique_ptr<TypeNode> returnType,
        std::vector<std::unique_ptr<ParameterNode>> parameters,
        std::unique_ptr<BlockNode> body
    );

    void setIdentifier(std::unique_ptr<IdentifierNode> identifier);
    void setReturnType(std::unique_ptr<TypeNode> returnType);
    void setParameters(std::vector<std::unique_ptr<ParameterNode>> parameters);
    void setBlock(std::unique_ptr<BlockNode> body);

private:
    std::unique_ptr<BlockNode> body;
    std::vector<std::unique_ptr<ParameterNode>> parameters;
    std::unique_ptr<IdentifierNode> identifier;
    std::unique_ptr<TypeNode> returnType;
};

// TODO: figure out what to do with returnType (SymbolTable.hpp)