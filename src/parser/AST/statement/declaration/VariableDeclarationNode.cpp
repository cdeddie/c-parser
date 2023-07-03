#include "parser/AST/statement/declaration/VariableDeclarationNode.hpp"
#include "parser/Visitor.hpp"

VariableDeclarationNode::VariableDeclarationNode(
    std::unique_ptr<TypeNode> type,
    std::unique_ptr<IdentifierNode> identifier,
    std::unique_ptr<ExpressionNode> init,
    int line,
    int column
)
    : DeclarationNode(std::move(type), std::move(identifier), line, column), 
      init(std::move(init))
{
}

const ExpressionNode& VariableDeclarationNode::getInit() const
{
    return *init;
}

void VariableDeclarationNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

