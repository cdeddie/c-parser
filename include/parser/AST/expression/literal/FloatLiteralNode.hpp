#pragma once

#include "parser/AST/expression/literal/LiteralNode.hpp"

class FloatLiteralNode : public LiteralNode
{
public:
    FloatLiteralNode(float value, int line = 0, int column = 0);
    float getValue() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    float value;
};