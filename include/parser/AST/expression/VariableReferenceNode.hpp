#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/IdentifierNode.hpp"

#include <memory>

class VariableReferenceNode : public ExpressionNode
{
public:
    VariableReferenceNode(std::unique_ptr<IdentifierNode> identifier);

    const IdentifierNode& getIdentifier() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    std::unique_ptr<IdentifierNode> identifier;
};