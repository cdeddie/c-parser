#include "parser/AST/statement/declaration/FunctionDeclarationNode.hpp"
#include "parser/Visitor.hpp"

// returnType, functionName and expression all exist as members of DeclarationNode
FunctionDeclarationNode::FunctionDeclarationNode(
    std::unique_ptr<TypeNode> returnType, 
    std::unique_ptr<IdentifierNode> functionName, 
    std::vector<std::unique_ptr<ParameterNode>> parameters,
    int line,
    int column
) 
    : DeclarationNode(std::move(returnType), std::move(functionName), line, column), 
      parameters(std::move(parameters))
{
}

const std::vector<std::unique_ptr<ParameterNode>>& FunctionDeclarationNode::getParameters() const
{
    return parameters;
}

void FunctionDeclarationNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

