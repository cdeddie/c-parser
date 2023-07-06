#pragma once

#include "parser/AST/statement/StatementNode.hpp"
#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/IdentifierNode.hpp"
#include "parser/AST/TypeNode.hpp"

#include <memory>

class VariableDeclarationNode : public StatementNode
{
public:
    VariableDeclarationNode(
        std::unique_ptr<TypeNode> type, 
        std::unique_ptr<IdentifierNode> identifier, 
        int line = 0,
        int column = 0
    );

    const TypeNode& getType() const;
    const IdentifierNode& getIdentifier() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    std::unique_ptr<TypeNode> type;
    std::unique_ptr<IdentifierNode> identifier;
};