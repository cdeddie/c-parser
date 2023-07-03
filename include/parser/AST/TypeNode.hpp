#pragma once

#include "parser/Node.hpp"

#include <string>

class TypeNode : public Node
{
public:
    TypeNode(const std::string& type, int line = 0, int column = 0);
    virtual ~TypeNode() = default;

    const std::string getType() const;
    
    virtual void accept(const Visitor& visitor) const override;
private:
    std::string type;
};