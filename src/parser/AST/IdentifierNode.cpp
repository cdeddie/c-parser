#include "parser/AST/IdentifierNode.hpp"
#include "parser/Visitor.hpp"

IdentifierNode::IdentifierNode(const std::string& name, int line, int column) 
    : Node(line, column), name(name)
{
}

const std::string& IdentifierNode::getName() const
{
    return name;
}

void IdentifierNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}