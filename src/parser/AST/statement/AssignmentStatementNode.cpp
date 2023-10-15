#include "parser/AST/statement/AssignmentStatementNode.hpp"
#include "parser/Visitor.hpp"

AssignmentStatementNode::AssignmentStatementNode(
    std::unique_ptr<VariableReferenceNode> varRef,
    std::unique_ptr<ExpressionNode> value,
    int dereferenceLevel,
    int line,
    int column
) 
    : StatementNode (line, column), 
      dereferenceLevel(dereferenceLevel), varRef(std::move(varRef)), value(std::move(value))
{
}

void AssignmentStatementNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}

const VariableReferenceNode& AssignmentStatementNode::getVarRef() const
{
    return *varRef;
}

const ExpressionNode& AssignmentStatementNode::getValue() const
{
    return *value;
}

const int AssignmentStatementNode::getDereferenceLevel() const
{
    return dereferenceLevel;
}