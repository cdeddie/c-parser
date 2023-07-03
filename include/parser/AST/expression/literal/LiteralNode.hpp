#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

class LiteralNode : public ExpressionNode
{
public:
    LiteralNode(int line = 0, int column = 0);
    virtual ~LiteralNode() = default;

    virtual void accept(const Visitor& visitor) const override;

};