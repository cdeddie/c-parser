#pragma once

#include "parser/Node.hpp"
#include <memory>

class AST
{
public:
	AST() : root(std::make_unique<Node>()) {}
	
	void setRoot(std::unique_ptr<Node> r) { root = std::move(r); }
	Node* getRoot() { return root.get(); }

	void traverse(Visitor& visitor) { root->accept(visitor); }

private:
	std::unique_ptr<Node> root;
};