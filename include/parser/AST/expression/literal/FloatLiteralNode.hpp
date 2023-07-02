#pragma once

#include "parser/AST/expression/literal/LiteralNode.hpp"

class FloatLiteralNode : public LiteralNode
{
public:
    FloatLiteralNode(float value);
    float getValue() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    float value;
};