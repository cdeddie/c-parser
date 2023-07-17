#include "parser/AST/statement/IfNode.hpp"
#include "parser/Visitor.hpp"

IfNode::IfNode(
    std::unique_ptr<ExpressionNode> condition, 
    std::unique_ptr<BlockNode> thenBlock,
    std::vector<ElseIfNode> elseIfBlocks,
    std::unique_ptr<BlockNode> elseBlock,
    int line,
    int column
)
    : condition(std::move(condition)), 
    thenBlock(std::move(thenBlock)), 
    elseIfBlocks(std::move(elseIfBlocks)), 
    elseBlock(std::move(elseBlock)),
    StatementNode(line, column)
{
}

const ExpressionNode& IfNode::getCondition() const
{
    return *condition;
}

const BlockNode& IfNode::getThenBlock() const
{
    return *thenBlock;
}

const std::vector<IfNode::ElseIfNode>& IfNode::getElseIfBlocks() const
{
    return elseIfBlocks;
}

const BlockNode* IfNode::getElseBlock() const
{
    return elseBlock.get();
}

void IfNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}