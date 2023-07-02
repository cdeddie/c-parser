#include "parser/AST/expression/literal/IntegerLiteralNode.hpp"
#include "parser/Visitor.hpp"

IntegerLiteralNode::IntegerLiteralNode(int value)
    : value(value)
{
}

int IntegerLiteralNode::getValue() const
{
    return value;
}

void IntegerLiteralNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}