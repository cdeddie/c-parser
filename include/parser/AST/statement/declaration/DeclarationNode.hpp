#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/TypeNode.hpp"
#include "parser/AST/IdentifierNode.hpp"
#include "parser/AST/statement/StatementNode.hpp"

#include <memory>

// DeclarationNode currently contains an ExpressionNode member
// May not be necessary, for example function declarations do not
// usually have expressions. Might change.
class DeclarationNode : public StatementNode 
{
public:
    DeclarationNode(
        std::unique_ptr<TypeNode> type, 
        std::unique_ptr<IdentifierNode> identifier
    );
    virtual ~DeclarationNode() = default; 

    const TypeNode& getType() const;
    const IdentifierNode& getIdentifier() const;

    virtual void accept(const Visitor& visitor) const override;

protected:
    std::unique_ptr<TypeNode> type;
    std::unique_ptr<IdentifierNode> identifier;
};
