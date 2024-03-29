#pragma once

#include "parser/AST/expression/literal/LiteralNode.hpp"

class CharLiteralNode : public LiteralNode
{
public:
    CharLiteralNode(char value, int line = 0, int column = 0);

    char getValue() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    char value;
};