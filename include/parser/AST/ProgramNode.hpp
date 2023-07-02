#pragma once

#include "parser/Node.hpp"

class ProgramNode : public Node
{
public:
    virtual void accept(const Visitor& visitor) const override;
};