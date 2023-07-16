#include "parser/AST/expression/FunctionCallExpressionNode.hpp"
#include "parser/Visitor.hpp"

FunctionCallExpressionNode::FunctionCallExpressionNode(
    std::unique_ptr<IdentifierNode> identifier, 
    std::vector<std::unique_ptr<ExpressionNode>> arguments,
    int line,
    int column
)
    : ExpressionNode(line, column), identifier(std::move(identifier)), arguments(std::move(arguments))
{
}

const IdentifierNode& FunctionCallExpressionNode::getIdentifier() const
{
    return *identifier;
}

const std::vector<std::unique_ptr<ExpressionNode>>& FunctionCallExpressionNode::getArguments() const
{
    return arguments;
}

void FunctionCallExpressionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}
