#pragma once

#include "parser/AST/statement/StatementNode.hpp"

#include <vector>
#include <memory>

class BlockNode : public Node
{
public:
    BlockNode(std::vector<std::unique_ptr<StatementNode>> statements, int line = 0, int column = 0);

    const std::vector<std::unique_ptr<StatementNode>>& getStatements() const;

    virtual void accept(const Visitor& visitor) const override;
    
private:
    std::vector<std::unique_ptr<StatementNode>> statements;
};