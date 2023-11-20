#pragma once

#include "parser/Node.hpp"
#include "parser/AST/ProgramNode.hpp"
#include "parser/PrintVisitor.hpp"
#include "parser/JsonExportVisitor.hpp"
#include <memory>

using json = nlohmann::json;

class AST
{
public:
    AST(std::unique_ptr<ProgramNode> node); 
    
    const ProgramNode& getRoot() const;
    
    void printTree(PrintVisitor& visitor);
    json toJson() const;
private:
    std::unique_ptr<ProgramNode> root;
};