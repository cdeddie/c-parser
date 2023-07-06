#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

#include <memory>
#include <string>

enum class BinaryOperatorType
{
    Plus, Minus, Multiply, Divide,              // +, -, *, /
    Modulus, And, Or,                           // %, &&, ||
    Equals, NotEquals, LessThan, GreaterThan,   // ==, !=, <, >
    LessThanOrEqual, GreaterThanOrEqual         // <=, >=
};

class BinaryExpressionNode : public ExpressionNode 
{
public:
    BinaryExpressionNode(
        std::unique_ptr<ExpressionNode> left, 
        std::unique_ptr<ExpressionNode> right, 
        BinaryOperatorType op,
        int line = 0,
        int column = 0
    );

    const ExpressionNode& getLeft() const;
    const ExpressionNode& getRight() const;
    const BinaryOperatorType getBinaryOperator() const;
    const std::string getBinaryOperatorString() const;

    virtual void accept(const Visitor& visitor) const override;

private:
    std::unique_ptr<ExpressionNode> left, right;
    BinaryOperatorType op;
};