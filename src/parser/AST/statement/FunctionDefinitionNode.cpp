#include "parser/AST/statement/FunctionDefinitionNode.hpp"
#include "parser/Visitor.hpp"

FunctionDefinitionNode::FunctionDefinitionNode(
    std::unique_ptr<TypeNode> returnType,
    std::unique_ptr<IdentifierNode> identifier,
    std::vector<std::unique_ptr<ParameterNode>> parameters,
    std::unique_ptr<BlockNode> body,
    int line,
    int column
) 
    : StatementNode(line, column), 
      identifier(std::move(identifier)), returnType(std::move(returnType)), 
      parameters(std::move(parameters)), body(std::move(body))
{
}

void FunctionDefinitionNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
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
