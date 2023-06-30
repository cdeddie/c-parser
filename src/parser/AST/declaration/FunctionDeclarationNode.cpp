#include "parser/AST/declaration/FunctionDeclarationNode.hpp"

// returnType, functionName and expression all exist as members of DeclarationNode
FunctionDeclarationNode::FunctionDeclarationNode(
    std::unique_ptr<TypeNode> returnType, 
    std::unique_ptr<IdentifierNode> functionName, 
    std::vector<SymbolInfo::Parameter> parameters
) 
    : DeclarationNode(std::move(returnType), std::move(functionName), nullptr), 
      parameters(std::move(parameters))
{
    
}

