#include "parser/AST/statement/StatementNode.hpp"
#include "parser/Visitor.hpp"

StatementNode::StatementNode(int line, int column)
    : Node(line, column)
{
}

void StatementNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}