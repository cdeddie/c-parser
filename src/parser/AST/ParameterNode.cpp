#include "parser/AST/ParameterNode.hpp"
#include "parser/Visitor.hpp"

ParameterNode::ParameterNode()
    : type(nullptr), identifier(nullptr)
{
}

ParameterNode::ParameterNode(
    std::unique_ptr<TypeNode> type, 
    std::unique_ptr<IdentifierNode> identifier,
    int line,
    int column
) 
    : Node(line, column), type(std::move(type)), identifier(std::move(identifier))
{
}

const TypeNode& ParameterNode::getType() const
{
    return *type;
}

const IdentifierNode& ParameterNode::getIdentifier() const
{
    return *identifier;
}

void ParameterNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}