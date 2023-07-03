#include "parser/AST/expression/literal/FloatLiteralNode.hpp"
#include "parser/Visitor.hpp"

FloatLiteralNode::FloatLiteralNode(float value, int line, int column)
    : LiteralNode(line, column), value(value)
{
}

float FloatLiteralNode::getValue() const
{
    return value;
}

void FloatLiteralNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}