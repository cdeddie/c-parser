#pragma once

#include "parser/Node.hpp"

class StatementNode : public Node
{
public:
	virtual ~StatementNode() = default;

    virtual void accept(const Visitor& visitor) const override;

};