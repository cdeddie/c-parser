#include "parser/AST/statement/FunctionDeclarationNode.hpp"
#include "parser/Visitor.hpp"

// returnType, functionName and expression all exist as members of DeclarationNode
FunctionDeclarationNode::FunctionDeclarationNode(
    std::unique_ptr<TypeNode> returnType, 
    std::unique_ptr<IdentifierNode> functionName, 
    std::vector<std::unique_ptr<ParameterNode>> parameters,
    int line,
    int column
) 
    : StatementNode(line, column), returnType(std::move(returnType)), functionName(std::move(functionName)), parameters(std::move(parameters)) 
{
}

const std::vector<std::unique_ptr<ParameterNode>>& FunctionDeclarationNode::getParameters() const
{
    return parameters;
}

const TypeNode& FunctionDeclarationNode::getReturnType() const
{
    return *returnType;
}

const IdentifierNode& FunctionDeclarationNode::getIdentifier() const
{
    return *functionName;
}

void FunctionDeclarationNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

