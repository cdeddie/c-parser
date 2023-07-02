#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

#include <memory>
#include <string>

// Unary Expression examples: -, ++, --, !, ~, &, *, sizeof, sizeof...

class UnaryExpressionNode : public ExpressionNode
{
public:
    UnaryExpressionNode(std::unique_ptr<ExpressionNode> operand, const std::string& op);

    const ExpressionNode& getOperand() const;
    const std::string& getOperator() const;

    virtual void accept(const Visitor& visitor) const override;

private:
	std::unique_ptr<ExpressionNode> operand;
	std::string op;
};