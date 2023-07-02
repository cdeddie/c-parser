#include "parser/AST/IdentifierNode.hpp"
#include "parser/Visitor.hpp"

IdentifierNode::IdentifierNode(const std::string& name) : name(name)
{
}

void IdentifierNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}