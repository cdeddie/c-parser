#include "parser/AST/expression/FunctionCallNode.hpp"

FunctionCallNode::FunctionCallNode(
    const std::string& functionName, 
    std::vector<std::unique_ptr<ExpressionNode>> arguments
)
    : functionName(functionName), arguments(std::move(arguments)) 
{
    
}

