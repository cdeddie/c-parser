#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

class FunctionCallNode : public ExpressionNode
{
public:
	FunctionCallNode(const std::string& functionName, std::vector<std::unique_ptr<ExpressionNode>> arguments);

private:
	std::string functionName;
	std::vector<std::unique_ptr<ExpressionNode>> arguments;
};