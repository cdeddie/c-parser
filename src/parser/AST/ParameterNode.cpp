#include "parser/AST/ParameterNode.hpp"

ParameterNode::ParameterNode()
    : type(nullptr), identifier(nullptr)
{
}

ParameterNode::ParameterNode(
    std::unique_ptr<TypeNode> type, 
    std::unique_ptr<IdentifierNode> identifier
) 
    : type(std::move(type)), identifier(std::move(identifier))
{

}