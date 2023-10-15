#include "parser/AST/statement/VariableDeclarationNode.hpp"
#include "parser/Visitor.hpp"

VariableDeclarationNode::VariableDeclarationNode(
    std::unique_ptr<TypeNode> type,
    std::unique_ptr<IdentifierNode> identifier,
    std::vector<std::unique_ptr<ArraySpecifierNode>> arraySpecifiers,
    int line,
    int column
)
    : StatementNode(line, column), 
    type(std::move(type)), 
    identifier(std::move(identifier)),
    arraySpecifiers(std::move(arraySpecifiers))
{
}

const TypeNode& VariableDeclarationNode::getType() const
{
    return *type;
}

const IdentifierNode& VariableDeclarationNode::getIdentifier() const
{
    return *identifier;
}

const std::vector<std::unique_ptr<ArraySpecifierNode>>& VariableDeclarationNode::getArraySpecifiers() const
{
    return arraySpecifiers;
}

void VariableDeclarationNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

