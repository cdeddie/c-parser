#pragma once

#include "parser/Node.hpp"

#include <string>

class IdentifierNode : public Node
{
public:
    IdentifierNode(const std::string& name);
    virtual ~IdentifierNode() = default;

    std::string getName() const { return name; }

    virtual void accept(const Visitor& visitor) const override;
private:
    std::string name;
};