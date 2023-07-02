#pragma once

#include "parser/AST/expression/literal/LiteralNode.hpp"

#include <string>

class StringLiteralNode : public LiteralNode
{
public:
    StringLiteralNode(std::string value);
    const std::string& getValue() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    std::string value;
};