#include "parser/Node.hpp"

void Node::addChild(std::unique_ptr<Node> child)
{
	children.push_back(std::move(child));
}