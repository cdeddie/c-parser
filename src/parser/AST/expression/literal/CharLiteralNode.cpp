#include "parser/AST/expression/literal/CharLiteralNode.hpp"
#include "parser/Visitor.hpp"

CharLiteralNode::CharLiteralNode(char value, int line, int column)
    : LiteralNode(line, column), value(value)
{
}

char CharLiteralNode::getValue() const
{
    return value;
}

void CharLiteralNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

