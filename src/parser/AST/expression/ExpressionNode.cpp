#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/Visitor.hpp"

ExpressionNode::ExpressionNode(int line, int column)
    : Node(line, column)
{
}

void ExpressionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}