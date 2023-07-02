#include "parser/AST/ProgramNode.hpp"
#include "parser/Visitor.hpp"

void ProgramNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}