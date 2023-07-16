#include "parser/AST/statement/ForNode.hpp"
#include "parser/Visitor.hpp"

ForNode::ForNode(
    std::unique_ptr<StatementNode> init, 
    std::unique_ptr<ExpressionNode> condition, 
    std::unique_ptr<ExpressionNode> increment, 
    std::vector<std::unique_ptr<StatementNode>> body,
    int line,
    int column
)
    : init(std::move(init)), 
    condition(std::move(condition)), 
    increment(std::move(increment)), 
    body(std::move(body)),
    StatementNode(line, column)
{
}

const StatementNode& ForNode::getInit() const
{
    return *init;
}

const ExpressionNode& ForNode::getCondition() const
{
    return *condition;
}

const ExpressionNode& ForNode::getIncrement() const
{
    return *increment;
}

const std::vector<std::unique_ptr<StatementNode>>& ForNode::getBody() const
{
    return body;
}

void ForNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}