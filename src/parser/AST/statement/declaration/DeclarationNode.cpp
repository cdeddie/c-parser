#include "parser/AST/statement/declaration/DeclarationNode.hpp"
#include "parser/Visitor.hpp"

DeclarationNode::DeclarationNode(
    std::unique_ptr<TypeNode> type, 
    std::unique_ptr<IdentifierNode> identifier
) 
    : type(std::move(type)), identifier(std::move(identifier))
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

void DeclarationNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}
