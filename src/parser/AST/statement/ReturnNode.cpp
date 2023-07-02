#include "parser/AST/statement/ReturnNode.hpp"
#include "parser/Visitor.hpp"

ReturnNode::ReturnNode(std::unique_ptr<ExpressionNode> expression)
    : expression(std::move(expression))
{
}

const ExpressionNode& ReturnNode::getExpression() const
{
    return *expression;
}

void ReturnNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}