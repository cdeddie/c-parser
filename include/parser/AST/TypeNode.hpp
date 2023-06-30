#pragma once

#include "parser/Node.hpp"

class TypeNode : public Node
{
public:
    TypeNode(const std::string& type);
    virtual ~TypeNode() = default;

    std::string getType() const { return type; }
private:
    std::string type;
};