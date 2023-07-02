#pragma once

#include "parser/AST/TypeNode.hpp"
#include "parser/AST/IdentifierNode.hpp"

#include <memory>

class ParameterNode : public Node
{
public:
    ParameterNode();
    ParameterNode(
        std::unique_ptr<TypeNode> type, 
        std::unique_ptr<IdentifierNode> identifier
    );

    const TypeNode& getType() const;
    const IdentifierNode& getIdentifier() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    std::unique_ptr<TypeNode> type;
    std::unique_ptr<IdentifierNode> identifier;
};