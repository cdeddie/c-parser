#include "parser/AST/ProgramNode.hpp"
#include "parser/Visitor.hpp"

void ProgramNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

ProgramNode::ProgramNode(std::vector<std::unique_ptr<StatementNode>> programNodes, int line, int column)
    : Node(line, column), programNodes(std::move(programNodes))
{
}