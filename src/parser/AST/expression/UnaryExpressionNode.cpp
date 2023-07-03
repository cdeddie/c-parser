#include "parser/AST/expression/UnaryExpressionNode.hpp"
#include "parser/Visitor.hpp"

UnaryExpressionNode::UnaryExpressionNode(
    std::unique_ptr<ExpressionNode> operand, 
    const std::string& op,
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

const std::string& UnaryExpressionNode::getOperator() const
{
    return op;
}

void UnaryExpressionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}