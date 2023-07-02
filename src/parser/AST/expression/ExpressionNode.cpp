#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/Visitor.hpp"

void ExpressionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}