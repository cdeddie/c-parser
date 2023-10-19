#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

#include <memory>

// Each specifierNode is a single array specifier, e.g. [5] or [x]
// A vector of these allows for multidemensional arrays e.g. int arr[5][5]

class ArraySpecifierNode : public Node
{
public:
    ArraySpecifierNode(std::unique_ptr<ExpressionNode> size = nullptr, int line = 0, int column = 0);

    const ExpressionNode& getSize() const;
    bool hasSize() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    std::unique_ptr<ExpressionNode> size;
};