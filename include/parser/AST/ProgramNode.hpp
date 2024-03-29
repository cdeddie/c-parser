#pragma once

#include "parser/AST/statement/StatementNode.hpp"

#include <vector>
#include <memory>

class ProgramNode : public Node
{
public:
    ProgramNode(std::vector<std::unique_ptr<StatementNode>> programNodes, int line, int column);

    const std::vector<std::unique_ptr<StatementNode>>& getStatements() const;

    virtual void accept(const Visitor& visitor) const override;


private:
    std::vector<std::unique_ptr<StatementNode>> programNodes;
};