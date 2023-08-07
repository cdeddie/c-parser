#include "parser/AST/TypeNode.hpp"
#include "parser/Visitor.hpp"

TypeNode::TypeNode(const std::string& type, int pointerLevel, int line, int column) 
    : Node(line, column), type(type), pointerLevel(pointerLevel)
{
}

const std::string TypeNode::getType() const
{
    return type;
}

const int TypeNode::getPointerLevel() const
{
    return pointerLevel;
}

void TypeNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}