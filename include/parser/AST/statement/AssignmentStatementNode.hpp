#pragma once

#include "parser/AST/expression/VariableReferenceNode.hpp"

class AssignmentStatementNode : public StatementNode 
{
public:
    AssignmentStatementNode(
        std::unique_ptr<VariableReferenceNode> varRef,
        std::unique_ptr<ExpressionNode> value,
        int dereferenceLevel = 0,
        int line = 0,
        int column = 0
    );

    const VariableReferenceNode& getVarRef() const;
    const ExpressionNode& getValue() const;
    const int getDereferenceLevel() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    std::unique_ptr<VariableReferenceNode> varRef;
    std::unique_ptr<ExpressionNode> value;
    int dereferenceLevel;
};