#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/BlockNode.hpp"

#include <memory>
#include <vector>
#include <utility>

class IfNode : public StatementNode 
{
public:
    using ElseIfNode = std::pair<std::unique_ptr<ExpressionNode>, std::unique_ptr<BlockNode>>;

    IfNode(
        std::unique_ptr<ExpressionNode> condition, 
        std::unique_ptr<BlockNode> thenBlock,
        std::vector<ElseIfNode> elseIfBlocks,
        std::unique_ptr<BlockNode> elseBlock,
        int line = 0,
        int column = 0
    );

    const ExpressionNode& getCondition() const;
    const BlockNode& getThenBlock() const;
    const std::vector<ElseIfNode>& getElseIfBlocks() const;
    const BlockNode* getElseBlock() const;
    
    virtual void accept(const Visitor& visitor) const override;

private:
    std::unique_ptr<ExpressionNode> condition;
    std::unique_ptr<BlockNode> thenBlock;
    std::vector<ElseIfNode> elseIfBlocks;
    std::unique_ptr<BlockNode> elseBlock;
};