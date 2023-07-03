#include "parser/AST/expression/VariableReferenceNode.hpp"
#include "parser/Visitor.hpp"

VariableReferenceNode::VariableReferenceNode(std::unique_ptr<IdentifierNode> identifier, int line, int column)
    : ExpressionNode(line, column), identifier(std::move(identifier))
{
}

const IdentifierNode& VariableReferenceNode::getIdentifier() const
{
    return *identifier;
}

void VariableReferenceNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}