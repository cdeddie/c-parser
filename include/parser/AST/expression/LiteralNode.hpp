#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

class LiteralNode : public ExpressionNode
{
public:
	LiteralNode(const std::string& value);
private:
	std::string value;
};