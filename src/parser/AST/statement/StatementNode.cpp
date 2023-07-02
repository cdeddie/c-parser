#include "parser/AST/statement/StatementNode.hpp"
#include "parser/Visitor.hpp"

void StatementNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}