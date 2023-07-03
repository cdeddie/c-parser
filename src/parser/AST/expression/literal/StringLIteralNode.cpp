#include "parser/AST/expression/literal/StringLiteralNode.hpp"
#include "parser/Visitor.hpp"

StringLiteralNode::StringLiteralNode(std::string value, int line, int column)
    : LiteralNode(line, column), value(value)
{
}

const std::string& StringLiteralNode::getValue() const
{
    return value;
}

void StringLiteralNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}