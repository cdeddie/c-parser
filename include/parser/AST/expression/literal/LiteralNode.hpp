#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

class LiteralNode : public ExpressionNode
{
public:
    virtual ~LiteralNode() = default;

    virtual void accept(const Visitor& visitor) const override;

};