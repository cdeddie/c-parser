#include "parser/AST/statement/FunctionCallStatementNode.hpp"
#include "parser/Visitor.hpp"

FunctionCallStatementNode::FunctionCallStatementNode(
    std::unique_ptr<IdentifierNode> identifier, 
    std::vector<std::unique_ptr<ExpressionNode>> arguments,
    int line,
    int column
)
    : StatementNode(line, column), identifier(std::move(identifier)), arguments(std::move(arguments))
{
}

const IdentifierNode& FunctionCallStatementNode::getIdentifier() const
{
    return *identifier;
}

const std::vector<std::unique_ptr<ExpressionNode>>& FunctionCallStatementNode::getArguments() const
{
    return arguments;
}

void FunctionCallStatementNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}