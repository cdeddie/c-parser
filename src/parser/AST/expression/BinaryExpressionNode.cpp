#include "parser/AST/expression/BinaryExpressionNode.hpp"

BinaryExpressionNode::BinaryExpressionNode(
    std::unique_ptr<ExpressionNode> left, 
    std::unique_ptr<ExpressionNode> right, 
    const std::string& op
)
    : left(std::move(left)), right(std::move(right)), op(op) 
{

}
