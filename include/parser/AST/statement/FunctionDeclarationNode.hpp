#pragma once

#include "parser/AST/ParameterNode.hpp"
#include "parser/AST/statement/StatementNode.hpp"

#include <vector>

class FunctionDeclarationNode : public StatementNode
{
public:
    FunctionDeclarationNode(
        std::unique_ptr<TypeNode> type, 
        std::unique_ptr<IdentifierNode> identifier, 
        std::vector<std::unique_ptr<ParameterNode>> parameters,
        int line = 0,
        int column = 0
    );

    const std::vector<std::unique_ptr<ParameterNode>>& getParameters() const;
    const TypeNode& getReturnType() const;
    const IdentifierNode& getIdentifier() const;

    virtual void accept(const Visitor& visitor) const override;

private:
    std::vector<std::unique_ptr<ParameterNode>> parameters;
    std::unique_ptr<TypeNode> returnType;
    std::unique_ptr<IdentifierNode> functionName;
};