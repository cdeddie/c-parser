#include "parser/AST/TypeNode.hpp"
#include "parser/Visitor.hpp"

TypeNode::TypeNode(const std::string& type) : type(type)
{
}

const std::string TypeNode::getType() const
{
    return type;
}

void TypeNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}