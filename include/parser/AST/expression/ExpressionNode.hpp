#pragma once

#include "parser/AST/statement/StatementNode.hpp"

class ExpressionNode : public StatementNode
{
public:
    ExpressionNode(int line = 0, int column = 0);
    virtual ~ExpressionNode() = default;

    virtual void accept(const Visitor& visitor) const override;
};