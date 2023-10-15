#pragma once

#include "parser/AST/statement/StatementNode.hpp"
#include "parser/AST/TypeNode.hpp"
#include "parser/AST/IdentifierNode.hpp"
#include "parser/AST/ArraySpecifierNode.hpp"

#include <memory>
#include <vector>

class VariableDefinitionNode : public StatementNode
{
public:
    VariableDefinitionNode(
        std::unique_ptr<TypeNode> type,
        std::unique_ptr<IdentifierNode> identifier,
        std::unique_ptr<Node> init,
        std::vector<std::unique_ptr<ArraySpecifierNode>> arraySpecifiers,
        int line = 0,
        int column = 0
    );

    virtual void accept(const Visitor& visitor) const override;

    const TypeNode& getType() const;
    const IdentifierNode& getIdentifier() const;
    const Node& getInit() const;
    const std::vector<std::unique_ptr<ArraySpecifierNode>>& getArraySpecifiers() const;

private:
    std::unique_ptr<TypeNode> type;
    std::unique_ptr<IdentifierNode> identifier;
    std::unique_ptr<Node> init;
    std::vector<std::unique_ptr<ArraySpecifierNode>> arraySpecifiers;
};