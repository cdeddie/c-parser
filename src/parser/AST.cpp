#include "parser/AST.hpp"

AST::AST(std::unique_ptr<ProgramNode> node)
    : root(std::move(node))
{

}

const ProgramNode& AST::getRoot() const
{
    return *root;
}

void AST::printTree(PrintVisitor& visitor)
{
    root->accept(visitor);
}

json AST::toJson() const
{
    JsonExportVisitor visitor;
    return visitor.toJson(*root);
}