#include "parser/AST/declaration/DeclarationNode.hpp"

class FunctionDeclarationNode : public DeclarationNode 
{
public:
    FunctionDeclarationNode(
        std::unique_ptr<TypeNode> type, 
        std::unique_ptr<IdentifierNode> identifier, 
        std::vector<SymbolInfo::Parameter> parameters
    );

private:
    std::vector<SymbolInfo::Parameter> parameters;
};