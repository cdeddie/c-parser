#pragma once

#include "parser/Node.hpp"

class IdentifierNode : public Node
{
public:
    IdentifierNode(const std::string& identifier);
    virtual ~IdentifierNode() = default;

    std::string getIdentifier() const { return identifier; }
private:
    std::string identifier;
};