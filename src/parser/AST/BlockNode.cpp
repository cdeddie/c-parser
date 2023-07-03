#include "parser/AST/BlockNode.hpp"
#include "parser/Visitor.hpp"

BlockNode::BlockNode()
{
}

BlockNode::BlockNode(std::vector<std::unique_ptr<StatementNode>> statements, int line, int column)
    : Node(line, column), statements(std::move(statements))
{
    // Push back every element in statements to children
    for (auto& statement : this->statements)
    {
        
    }
}

const std::vector<std::unique_ptr<StatementNode>>& BlockNode::getStatements() const
{
    return statements;
}

void BlockNode::addStatement(std::unique_ptr<StatementNode> statement)
{
    statements.push_back(std::move(statement));
}

void BlockNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}