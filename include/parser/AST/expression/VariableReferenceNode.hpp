#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/IdentifierNode.hpp"

#include <memory>
#include <vector>

class VariableReferenceNode : public ExpressionNode
{
public:
    VariableReferenceNode(
        std::unique_ptr<IdentifierNode> identifier, 
        std::vector<std::unique_ptr<ExpressionNode>> indices = {},
        int line = 0, int column = 0);

    const IdentifierNode& getIdentifier() const;
    const std::vector<std::unique_ptr<ExpressionNode>>& getIndices() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    std::unique_ptr<IdentifierNode> identifier;
    std::vector<std::unique_ptr<ExpressionNode>> indices;
};