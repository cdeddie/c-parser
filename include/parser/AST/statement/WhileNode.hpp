#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/BlockNode.hpp"

#include <memory>

class WhileNode : public StatementNode 
{
public:
    WhileNode(
        std::unique_ptr<ExpressionNode> condition, 
        std::unique_ptr<BlockNode> body,
        int line = 0,
        int column = 0
    );

    const ExpressionNode& getCondition() const;
    const BlockNode& getBody() const;
    
    virtual void accept(const Visitor& visitor) const override;

private:
    std::unique_ptr<ExpressionNode> condition;
    std::unique_ptr<BlockNode> body;
};