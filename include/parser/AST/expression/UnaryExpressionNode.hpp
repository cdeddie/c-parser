#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

#include <memory>
#include <string>

// Unary Expression examples: -, ++, --, !, &, *, sizeof, sizeof...

enum class UnaryOperatorType
{
    Negate,     // -1
    Not,        // !true
    Increment,  // ++i
    Decrement   // --i
};

class UnaryExpressionNode : public ExpressionNode
{
public:
    UnaryExpressionNode(
        std::unique_ptr<ExpressionNode> operand, 
        UnaryOperatorType op,
        int line = 0,
        int column = 0
    );

    const ExpressionNode& getOperand() const;
    const UnaryOperatorType getUnaryOperatorType() const;
    const std::string getUnaryOperatorString() const;
    

    virtual void accept(const Visitor& visitor) const override;

private:
    std::unique_ptr<ExpressionNode> operand;
    UnaryOperatorType op;
};