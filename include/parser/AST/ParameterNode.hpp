#pragma once

#include "parser/Node.hpp"
#include "parser/AST/TypeNode.hpp"
#include "parser/AST/IdentifierNode.hpp"

class ParameterNode : public Node
{
public:
    ParameterNode();
    ParameterNode(
        std::unique_ptr<TypeNode> type, 
        std::unique_ptr<IdentifierNode> identifier
    );
private:
    std::unique_ptr<TypeNode> type;
    std::unique_ptr<IdentifierNode> identifier;
};