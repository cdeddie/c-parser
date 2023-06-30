#include "parser/AST/expression/UnaryExpressionNode.hpp"

UnaryExpressionNode::UnaryExpressionNode(
    std::unique_ptr<ExpressionNode> operand, 
    const std::string& op
)
    : operand(std::move(operand)), op(op) 
{
    
}
