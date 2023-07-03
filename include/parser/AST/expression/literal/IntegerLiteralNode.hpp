#pragma once

#include "parser/AST/expression/literal/LiteralNode.hpp"

class IntegerLiteralNode : public LiteralNode
{
public:
    IntegerLiteralNode(int value, int line = 0, int column = 0);

    int getValue() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    int value;
};