#pragma once

#include "parser/Node.hpp"

#include <string>

class TypeNode : public Node
{
public:
    TypeNode(const std::string& type, int pointerLevel = 0, int line = 0, int column = 0);
    virtual ~TypeNode() = default;

    const std::string getType() const;
    const int getPointerLevel() const;
    
    virtual void accept(const Visitor& visitor) const override;
private:
    std::string type;
    int pointerLevel; // 0 = no pointer, >0 for pointer
};