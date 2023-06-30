#pragma once

#include <vector>
#include <memory>
#include "parser/Environment.hpp"
#include "parser/Visitor.hpp"

class Node
{
public:
	virtual ~Node() = default;

	void addChild(std::unique_ptr<Node> child);

	// Method for node traversal in subclasses
	virtual void accept(Visitor& visitor)
    {
        for (auto& child : children)
        {
            child->accept(visitor);
        }
    }

protected:
	std::vector<std::unique_ptr<Node>> children;
};