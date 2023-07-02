#pragma once

class Visitor;

class Node
{
public:
	virtual ~Node() = default;

	// Method for node traversal in subclasses
    virtual void accept(const Visitor& visitor) const = 0;

};