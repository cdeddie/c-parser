#pragma once

#include "parser/Node.hpp"

class ExpressionNode : public Node
{
public:
    ExpressionNode(int line = 0, int column = 0);
    virtual ~ExpressionNode() = default;

    virtual void accept(const Visitor& visitor) const override;
};