#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

class BinaryExpressionNode : public ExpressionNode 
{
public:
	BinaryExpressionNode(
		std::unique_ptr<ExpressionNode> left, 
		std::unique_ptr<ExpressionNode> right, 
		const std::string& op
	);

private:
	std::unique_ptr<ExpressionNode> left, right;
	std::string op;
};