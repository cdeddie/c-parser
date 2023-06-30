#include "parser/AST/declaration/DeclarationNode.hpp"

DeclarationNode::DeclarationNode(
    std::unique_ptr<TypeNode> type, 
    std::unique_ptr<IdentifierNode> identifier, 
    std::unique_ptr<ExpressionNode> expression
) 
    : type(std::move(type)), identifier(std::move(identifier)), expression(std::move(expression))
{
	
}

const TypeNode& DeclarationNode::getType() const
{
    return *type;
}

const IdentifierNode& DeclarationNode::getIdentifier() const
{
    return *identifier;
}

const ExpressionNode& DeclarationNode::getExpression() const
{
    return *expression;
}
