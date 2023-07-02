#pragma once

#include "parser/AST/statement/declaration/DeclarationNode.hpp"
#include "parser/AST/ParameterNode.hpp"

#include <vector>

class FunctionDeclarationNode : public DeclarationNode 
{
public:
    FunctionDeclarationNode(
        std::unique_ptr<TypeNode> type, 
        std::unique_ptr<IdentifierNode> identifier, 
        std::vector<std::unique_ptr<ParameterNode>> parameters
    );

    virtual void accept(const Visitor& visitor) const override;

private:
    std::vector<std::unique_ptr<ParameterNode>> parameters;
};