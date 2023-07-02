#include "parser/AST/expression/BinaryExpressionNode.hpp"
#include "parser/Visitor.hpp"

BinaryExpressionNode::BinaryExpressionNode(
    std::unique_ptr<ExpressionNode> left, 
    std::unique_ptr<ExpressionNode> right, 
    const std::string& op
)
    : left(std::move(left)), right(std::move(right)), op(op) 
{
}

const ExpressionNode& BinaryExpressionNode::getLeft() const
{
    return *left;
}

const ExpressionNode& BinaryExpressionNode::getRight() const
{
    return *right;
}

const std::string& BinaryExpressionNode::getOperator() const
{
    return op;
}

void BinaryExpressionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}
