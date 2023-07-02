#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

#include <memory>
#include <string>

class BinaryExpressionNode : public ExpressionNode 
{
public:
    BinaryExpressionNode(
        std::unique_ptr<ExpressionNode> left, 
        std::unique_ptr<ExpressionNode> right, 
        const std::string& op
    );

    const ExpressionNode& getLeft() const;
    const ExpressionNode& getRight() const;
    const std::string& getOperator() const;

    virtual void accept(const Visitor& visitor) const override;

private:
    std::unique_ptr<ExpressionNode> left, right;
    std::string op;
};