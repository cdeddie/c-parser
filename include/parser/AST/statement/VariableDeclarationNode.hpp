#pragma once

#include "parser/AST/statement/StatementNode.hpp"
#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/IdentifierNode.hpp"
#include "parser/AST/TypeNode.hpp"
#include "parser/AST/ArraySpecifierNode.hpp"

#include <vector>

// int a || int a[5]

class VariableDeclarationNode : public StatementNode
{
public:
    VariableDeclarationNode(
        std::unique_ptr<TypeNode> type, 
        std::unique_ptr<IdentifierNode> identifier, 
        std::vector<std::unique_ptr<ArraySpecifierNode>> arraySpecifiers,
        int line = 0,
        int column = 0
    );

    const TypeNode& getType() const;
    const IdentifierNode& getIdentifier() const;
    const std::vector<std::unique_ptr<ArraySpecifierNode>>& getArraySpecifiers() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    std::unique_ptr<TypeNode> type;
    std::unique_ptr<IdentifierNode> identifier;
    std::vector<std::unique_ptr<ArraySpecifierNode>> arraySpecifiers;
};