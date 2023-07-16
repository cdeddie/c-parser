#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/IdentifierNode.hpp"

#include <vector>
#include <memory>

class FunctionCallExpressionNode : public ExpressionNode
{
public:
    FunctionCallExpressionNode(
        std::unique_ptr<IdentifierNode> identifier, 
        std::vector<std::unique_ptr<ExpressionNode>> arguments,
        int line = 0,
        int column = 0
    );

    const IdentifierNode& getIdentifier() const;
    const std::vector<std::unique_ptr<ExpressionNode>>& getArguments() const;

    virtual void accept(const Visitor& visitor) const override;

private:
    std::unique_ptr<IdentifierNode> identifier;
    std::vector<std::unique_ptr<ExpressionNode>> arguments;
};