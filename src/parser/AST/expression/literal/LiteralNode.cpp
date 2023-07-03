#include "parser/AST/expression/literal/LiteralNode.hpp"
#include "parser/Visitor.hpp"

LiteralNode::LiteralNode(int line, int column)
    : ExpressionNode(line, column)
{
}

void LiteralNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}