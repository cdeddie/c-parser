#include "parser/AST/expression/BinaryExpressionNode.hpp"
#include "parser/Visitor.hpp"

BinaryExpressionNode::BinaryExpressionNode(
    std::unique_ptr<ExpressionNode> left, 
    std::unique_ptr<ExpressionNode> right, 
    BinaryOperatorType op,
    int line,
    int column
)
    : ExpressionNode(line, column), left(std::move(left)), right(std::move(right)), op(op)
{
}

const ExpressionNode& BinaryExpressionNode::getLeft() const
{
    return *left;
}

const ExpressionNode& BinaryExpressionNode::getRight() const
{
    return *right;
}

const BinaryOperatorType BinaryExpressionNode::getBinaryOperator() const
{
    return op;
}

void BinaryExpressionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

const std::string BinaryExpressionNode::getBinaryOperatorString() const
{
    switch (op)
    {
        case BinaryOperatorType::Plus:
            return "+";
        case BinaryOperatorType::Minus:
            return "-";
        case BinaryOperatorType::Multiply:
            return "*";
        case BinaryOperatorType::Divide:
            return "/";
        case BinaryOperatorType::Modulus:
            return "%";
        case BinaryOperatorType::And:
            return "&&";
        case BinaryOperatorType::Or:
            return "||";
        case BinaryOperatorType::Equals:
            return "==";
        case BinaryOperatorType::NotEquals:
            return "!=";
        case BinaryOperatorType::LessThan:
            return "<";
        case BinaryOperatorType::GreaterThan:
            return ">";
        case BinaryOperatorType::LessThanOrEqual:
            return "<=";
        case BinaryOperatorType::GreaterThanOrEqual:
            return ">=";
        default:
            return "";
    }
}
