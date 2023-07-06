#include "parser/AST/statement/VariableDeclarationNode.hpp"
#include "parser/Visitor.hpp"

VariableDeclarationNode::VariableDeclarationNode(
    std::unique_ptr<TypeNode> type,
    std::unique_ptr<IdentifierNode> identifier,
    int line,
    int column
)
    : StatementNode(line, column), type(std::move(type)), identifier(std::move(identifier))
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

void VariableDeclarationNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

