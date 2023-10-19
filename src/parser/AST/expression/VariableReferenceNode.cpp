#include "parser/AST/expression/VariableReferenceNode.hpp"
#include "parser/Visitor.hpp"

VariableReferenceNode::VariableReferenceNode(
    std::unique_ptr<IdentifierNode> identifier, 
    std::vector<std::unique_ptr<ExpressionNode>> indices,
    int line, int column)
    : ExpressionNode(line, column), identifier(std::move(identifier)), indices(std::move(indices))
{
}

const IdentifierNode& VariableReferenceNode::getIdentifier() const
{
    return *identifier;
}

const std::vector<std::unique_ptr<ExpressionNode>>& VariableReferenceNode::getIndices() const
{
    return indices;
}

void VariableReferenceNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}