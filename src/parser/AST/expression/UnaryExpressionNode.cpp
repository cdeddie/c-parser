#include "parser/AST/expression/UnaryExpressionNode.hpp"
#include "parser/Visitor.hpp"

UnaryExpressionNode::UnaryExpressionNode(
    std::unique_ptr<ExpressionNode> operand, 
    UnaryOperatorType op,
    int line,
    int column
)
    : ExpressionNode(line, column), operand(std::move(operand)), op(op)
{
}

const ExpressionNode& UnaryExpressionNode::getOperand() const
{
    return *operand;
}

const UnaryOperatorType UnaryExpressionNode::getUnaryOperatorType() const
{
    return op;
}

const std::string UnaryExpressionNode::getUnaryOperatorString() const
{
    switch (op)
    {
        case UnaryOperatorType::Negate:
            return "-";
        case UnaryOperatorType::Not:
            return "!";
        case UnaryOperatorType::Increment:
            return "++";
        case UnaryOperatorType::Decrement:
            return "--";
        case UnaryOperatorType::AddressOf:
            return "&";
        case UnaryOperatorType::Dereference:
            return "* (dereference)";
        default:
            return "";
    }
}

void UnaryExpressionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}