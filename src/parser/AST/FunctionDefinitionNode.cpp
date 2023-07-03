#include "parser/AST/FunctionDefinitionNode.hpp"
#include "parser/Visitor.hpp"

FunctionDefinitionNode::FunctionDefinitionNode()
    : identifier(nullptr), returnType(nullptr), body(nullptr)
{
}

FunctionDefinitionNode::FunctionDefinitionNode(
    std::unique_ptr<IdentifierNode> identifier,
    std::unique_ptr<TypeNode> returnType,
    std::vector<std::unique_ptr<ParameterNode>> parameters,
    std::unique_ptr<BlockNode> body,
    int line,
    int column
) 
    : Node(line, column), 
      identifier(std::move(identifier)), returnType(std::move(returnType)), 
      parameters(std::move(parameters)), body(std::move(body))
{
}

void FunctionDefinitionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

void FunctionDefinitionNode::setIdentifier(std::unique_ptr<IdentifierNode> identifier)
{
    this->identifier = std::move(identifier);
}

void FunctionDefinitionNode::setReturnType(std::unique_ptr<TypeNode> returnType)
{
    this->returnType = std::move(returnType);
}

void FunctionDefinitionNode::setParameters(std::vector<std::unique_ptr<ParameterNode>> parameters)
{
    this->parameters = std::move(parameters);
}

void FunctionDefinitionNode::setBlock(std::unique_ptr<BlockNode> body)
{
    this->body = std::move(body);
}

const IdentifierNode& FunctionDefinitionNode::getIdentifier() const
{
    return *identifier;
}

const TypeNode& FunctionDefinitionNode::getReturnType() const
{
    return *returnType;
}

const std::vector<std::unique_ptr<ParameterNode>>& FunctionDefinitionNode::getParameters() const
{
    return parameters;
}

const BlockNode& FunctionDefinitionNode::getBlock() const
{
    return *body;
}
