#pragma once

#include "parser/Node.hpp"
#include "parser/AST/ProgramNode.hpp"
#include "parser/PrintVisitor.hpp"
#include "parser/HTMLVisitor.hpp"
#include <memory>

class AST
{
public:
    AST(std::unique_ptr<ProgramNode> node); 
    
    const ProgramNode& getRoot() const;
    
    void printTree(PrintVisitor& visitor);
    void printHTML(HTMLVisitor& visitor);
private:
    std::unique_ptr<ProgramNode> root;
};
