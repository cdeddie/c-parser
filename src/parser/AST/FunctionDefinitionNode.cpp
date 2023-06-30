#include "parser/AST/FunctionDefinitionNode.hpp"

FunctionDefinitionNode::FunctionDefinitionNode()
    : identifier(nullptr), returnType(nullptr), body(nullptr)
{
}

FunctionDefinitionNode::FunctionDefinitionNode(
    std::unique_ptr<IdentifierNode> identifier,
    std::unique_ptr<TypeNode> returnType,
    std::vector<std::unique_ptr<ParameterNode>> parameters,
    std::unique_ptr<BlockNode> body
) 
    : identifier(std::move(identifier)), returnType(std::move(returnType)), parameters(std::move(parameters)), body(std::move(body))
{
}

void FunctionDefinitionNode::setIdentifier(std::unique_ptr<IdentifierNode> identifier)
{
    this->identifier = std::move(identifier);
    children.push_back(std::move(identifier));
}

void FunctionDefinitionNode::setReturnType(std::unique_ptr<TypeNode> returnType)
{
    this->returnType = std::move(returnType);
    children.push_back(std::move(returnType));
}

void FunctionDefinitionNode::setParameters(std::vector<std::unique_ptr<ParameterNode>> parameters)
{
    this->parameters = std::move(parameters);
    for (auto& parameter : this->parameters)
    {
        children.push_back(std::move(parameter));
    }
}

void FunctionDefinitionNode::setBlock(std::unique_ptr<BlockNode> body)
{
    this->body = std::move(body);
    children.push_back(std::move(body));
}