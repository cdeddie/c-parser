#include "parser/AST/declaration/VariableDeclarationNode.hpp"

VariableDeclarationNode::VariableDeclarationNode(
    std::unique_ptr<TypeNode> type,
    std::unique_ptr<IdentifierNode> identifier,
    std::unique_ptr<ExpressionNode> expression
)
    : DeclarationNode(std::move(type), std::move(identifier), std::move(expression))
{
    
}


