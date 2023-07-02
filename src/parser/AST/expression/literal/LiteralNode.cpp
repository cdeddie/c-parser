#include "parser/AST/expression/literal/LiteralNode.hpp"
#include "parser/Visitor.hpp"

void LiteralNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}