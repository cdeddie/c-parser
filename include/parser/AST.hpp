#pragma once

#include "parser/Node.hpp"
#include "parser/AST/ProgramNode.hpp"
#include <memory>

class AST
{
public:
    AST() : root(std::make_unique<ProgramNode>()) {}
    
    // void setRoot(std::unique_ptr<Node> r) { root = std::move(r); }
    // Node* getRoot() { return root.get(); }

    // void traverse(Visitor& visitor) { root->accept(visitor); }

private:
    std::unique_ptr<Node> root;
};