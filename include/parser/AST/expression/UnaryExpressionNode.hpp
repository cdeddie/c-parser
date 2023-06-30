#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

// Unary Expression examples: -, ++, --, !, ~, &, *, sizeof, sizeof...

class UnaryExpressionNode : public ExpressionNode
{
public:
    UnaryExpressionNode(std::unique_ptr<ExpressionNode> operand, const std::string& op);

private:
	std::unique_ptr<ExpressionNode> operand;
	std::string op;
};