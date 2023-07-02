#include "parser/AST/expression/FunctionCallNode.hpp"
#include "parser/Visitor.hpp"

FunctionCallNode::FunctionCallNode(
    std::unique_ptr<IdentifierNode> identifier, 
    std::vector<std::unique_ptr<ExpressionNode>> arguments
)
    : identifier(std::move(identifier)), arguments(std::move(arguments))
{
}

const IdentifierNode& FunctionCallNode::getIdentifier() const
{
    return *identifier;
}

const std::vector<std::unique_ptr<ExpressionNode>>& FunctionCallNode::getArguments() const
{
    return arguments;
}

void FunctionCallNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}
