#include "parser/AST/statement/VariableDefinitionNode.hpp"
#include "parser/Visitor.hpp"

VariableDefinitionNode::VariableDefinitionNode(
    std::unique_ptr<TypeNode> type,
    std::unique_ptr<IdentifierNode> identifier,
    std::unique_ptr<ExpressionNode> init,
    int line,
    int column
) 
    : StatementNode (line, column), 
      type(std::move(type)), identifier(std::move(identifier)), init(std::move(init))
{
}

void VariableDefinitionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

const TypeNode& VariableDefinitionNode::getType() const
{
    return *type;
}

const IdentifierNode& VariableDefinitionNode::getIdentifier() const
{
    return *identifier;
}

const ExpressionNode& VariableDefinitionNode::getInit() const
{
    return *init;
}

