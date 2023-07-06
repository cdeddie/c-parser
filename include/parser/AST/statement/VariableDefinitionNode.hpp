#pragma once

#include "parser/Node.hpp"
#include "parser/AST/statement/StatementNode.hpp"
#include "parser/AST/TypeNode.hpp"
#include "parser/AST/IdentifierNode.hpp"
#include "parser/AST/expression/ExpressionNode.hpp"

#include <memory>

class VariableDefinitionNode : public StatementNode
{
public:
    VariableDefinitionNode(
        std::unique_ptr<TypeNode> type,
        std::unique_ptr<IdentifierNode> identifier,
        std::unique_ptr<ExpressionNode> init,
        int line = 0,
        int column = 0
    );

    virtual void accept(const Visitor& visitor) const override;

    const TypeNode& getType() const;
    const IdentifierNode& getIdentifier() const;
    const ExpressionNode& getInit() const;
private:
    std::unique_ptr<TypeNode> type;
    std::unique_ptr<IdentifierNode> identifier;
    std::unique_ptr<ExpressionNode> init;
};