#pragma once

#include "parser/AST/statement/StatementNode.hpp"
#include "parser/AST/expression/ExpressionNode.hpp"

#include <memory>

class ReturnNode : public StatementNode 
{
public:
    ReturnNode(std::unique_ptr<ExpressionNode> expression);

    const ExpressionNode& getExpression() const;

    virtual void accept(const Visitor& visitor) const override;

private:
    std::unique_ptr<ExpressionNode> expression;
};