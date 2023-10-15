#include "parser/AST/expression/ArrayInitializerNode.hpp"
#include "parser/Visitor.hpp"

ArrayInitializerNode::ArrayInitializerNode(std::vector<std::unique_ptr<ExpressionNode>> elements, int line, int column)
    : ExpressionNode(line, column), elements(std::move(elements))
{
}

const std::vector<std::unique_ptr<ExpressionNode>>& ArrayInitializerNode::getElements() const
{
    return elements;
}

void ArrayInitializerNode::accept(const Visitor& visitor) const
{
    visitor.visit(*this);
}