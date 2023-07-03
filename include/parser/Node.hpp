#pragma once

class Visitor; // Ensure that circular dependencies do not occur

class Node
{
public:
    Node(int line = 0, int column = 0);
    virtual ~Node() = default;

    // Method for node traversal in subclasses
    virtual void accept(const Visitor& visitor) const = 0;

    int getLine() const;
    int getColumn() const;

private:
    int line;
    int column;
};