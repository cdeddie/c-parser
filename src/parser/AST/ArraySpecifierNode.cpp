#include "parser/AST/ArraySpecifierNode.hpp"
#include "parser/Visitor.hpp"

ArraySpecifierNode::ArraySpecifierNode(std::unique_ptr<ExpressionNode> size, int line, int column)
    : Node(line, column), size(std::move(size))
{
}

const ExpressionNode& ArraySpecifierNode::getSize() const
{
    return *size;
}

bool ArraySpecifierNode::hasSize() const
{
    return size != nullptr;
}

void ArraySpecifierNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}