#pragma once

#include "parser/Node.hpp"

class StatementNode : public Node
{
public:
    StatementNode(int line = 0, int column = 0);
	virtual ~StatementNode() = default;

    virtual void accept(const Visitor& visitor) const override;

};