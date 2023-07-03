#pragma once

#include "parser/Node.hpp"

#include <string>

class IdentifierNode : public Node
{
public:
    IdentifierNode(const std::string& name, int line = 0, int column = 0);
    virtual ~IdentifierNode() = default;

    const std::string& getName() const;

    virtual void accept(const Visitor& visitor) const override;
private:
    std::string name;
};