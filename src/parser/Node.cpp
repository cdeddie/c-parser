#include "parser/Node.hpp"

Node::Node(int line, int column) : line(line), column(column)
{
}

int Node::getLine() const
{
    return line;
}

int Node::getColumn() const
{
    return column;
}
