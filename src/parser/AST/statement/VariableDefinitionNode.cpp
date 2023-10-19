#include "parser/AST/statement/VariableDefinitionNode.hpp"
#include "parser/Visitor.hpp"

VariableDefinitionNode::VariableDefinitionNode(
    std::unique_ptr<TypeNode> type,
    std::unique_ptr<IdentifierNode> identifier,
    std::unique_ptr<Node> init,
    std::vector<std::unique_ptr<ArraySpecifierNode>> arraySpecifiers,
    int line,
    int column
) 
    : StatementNode (line, column), 
      type(std::move(type)), identifier(std::move(identifier)), init(std::move(init)), arraySpecifiers(std::move(arraySpecifiers))
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

const Node& VariableDefinitionNode::getInit() const
{
    return *init;
}

const std::vector<std::unique_ptr<ArraySpecifierNode>>& VariableDefinitionNode::getArraySpecifiers() const
{
    return arraySpecifiers;
}

