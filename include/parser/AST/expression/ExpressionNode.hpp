#pragma once

#include "parser/Node.hpp"

class ExpressionNode : public Node
{
public:
    virtual ~ExpressionNode() = default;

    virtual void accept(const Visitor& visitor) const override;
};