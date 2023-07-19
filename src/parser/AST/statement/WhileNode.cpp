#include "parser/AST/statement/WhileNode.hpp"
#include "parser/Visitor.hpp"

WhileNode::WhileNode(
    std::unique_ptr<ExpressionNode> condition, 
    std::unique_ptr<BlockNode> body,
    int line,
    int column
)
    : condition(std::move(condition)), body(std::move(body)), StatementNode(line, column)
{
}

const ExpressionNode& WhileNode::getCondition() const
{
    return *condition;
}

const BlockNode& WhileNode::getBody() const
{
    return *body;
}

void WhileNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}