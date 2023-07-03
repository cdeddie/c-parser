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
        std::vector<std::unique_ptr<ParameterNode>> parameters,
        int line = 0,
        int column = 0
    );

    const std::vector<std::unique_ptr<ParameterNode>>& getParameters() const;

    virtual void accept(const Visitor& visitor) const override;

private:
    std::vector<std::unique_ptr<ParameterNode>> parameters;
};