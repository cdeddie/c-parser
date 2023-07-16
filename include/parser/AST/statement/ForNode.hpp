#pragma once
#include "parser/AST/expression/ExpressionNode.hpp"

#include <memory>
#include <vector>

class ForNode : public StatementNode
{
public:
    ForNode(
        std::unique_ptr<StatementNode> init, 
        std::unique_ptr<ExpressionNode> condition, 
        std::unique_ptr<ExpressionNode> increment, 
        std::vector<std::unique_ptr<StatementNode>> body,
        int line = 0,
        int column = 0
    );

    const StatementNode& getInit() const;
    const ExpressionNode& getCondition() const;
    const ExpressionNode& getIncrement() const;
    const std::vector<std::unique_ptr<StatementNode>>& getBody() const;
    
    virtual void accept(const Visitor& visitor) const override;
private:
    std::unique_ptr<StatementNode> init;
    std::unique_ptr<ExpressionNode> condition;
    std::unique_ptr<ExpressionNode> increment;
    std::vector<std::unique_ptr<StatementNode>> body;
};