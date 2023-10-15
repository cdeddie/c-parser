#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"

#include <memory>
#include <vector>

class ArrayInitializerNode : public ExpressionNode 
{
public:
    ArrayInitializerNode(std::vector<std::unique_ptr<ExpressionNode>> elements, int line = 0, int column = 0);

    const std::vector<std::unique_ptr<ExpressionNode>>& getElements() const;
    virtual void accept(const Visitor& visitor) const override;
private:
    std::vector<std::unique_ptr<ExpressionNode>> elements;
};