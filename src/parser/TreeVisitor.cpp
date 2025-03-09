#include "parser/TreeVisitor.hpp"

void TreeVisitor::visit(const BlockNode& node) const
{
    json += "{\"name\": \"Block\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";

    const auto& statements = node.getStatements();
    if (statements.size() == 1)
    {
        statements[0]->accept(*this);
    }
    else
    {
        for (size_t i = 0; i < statements.size(); ++i) 
        {
            statements[i]->accept(*this);
            if (i < statements.size() - 1) 
            {
                json += ",";
            }
        }
    }

    json += "]}";
}

void TreeVisitor::visit(const FunctionDefinitionNode& node) const
{
    json += "{\"name\": \"Function Definition\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";

    node.getIdentifier().accept(*this);
    json += ",";
    node.getReturnType().accept(*this);
    

    for (const auto& parameter : node.getParameters()) 
    {
        json += ",";
        parameter->accept(*this);
    }

    json += ",";
    node.getBlock().accept(*this);
    json += "]}";
}

void TreeVisitor::visit(const IdentifierNode& node) const
{
    json += "{";
    json += "\"name\": \"Identifier\",";
    json += "\"attributes\": {\"identifier\": \"" + node.getName() + "\", \"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "}";
    json += "}";
}

void TreeVisitor::visit(const ParameterNode& node) const
{
    json += "{";
    json += "\"name\": \"Parameter\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    
    node.getType().accept(*this);
    json += ",";
    node.getIdentifier().accept(*this);
    
    json += "]}";
}

void TreeVisitor::visit(const ProgramNode& node) const
{
    json += "{";
    json += "\"name\": \"AST\",";
    json += "\"children\": [";

    const auto& statements = node.getStatements();
    for (size_t i = 0; i < statements.size(); ++i) 
    {
        statements[i]->accept(*this);
        if (i < statements.size() - 1) 
        {
            json += ",";
        }
    }
    
    json += "]}";
}

void TreeVisitor::visit(const TypeNode& node) const
{
    json += "{";
    json += "\"name\": \"Type\",";
    json += "\"attributes\": {\"datatype\": \"" + node.getType() + "\", \"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn());
    
    if (node.getPointerLevel() > 0)
    {
        json += ", \"pointerLevel\": " + std::to_string(node.getPointerLevel());
    }
    
    json += "}}";
}

void TreeVisitor::visit(const BinaryExpressionNode& node) const
{
    json += "{";
    json += "\"name\": \"Binary Expression\",";
    json += "\"attributes\": {\"operator\": \"" + node.getBinaryOperatorString() + "\", \"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getLeft().accept(*this);
    json += ",";
    node.getRight().accept(*this);
    json += "]}";
}

void TreeVisitor::visit(const FunctionCallExpressionNode& node) const
{
    json += "{";
    json += "\"name\": \"Function Call\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getIdentifier().accept(*this);
    const auto& arguments = node.getArguments();
    for (size_t i = 0; i < arguments.size(); i++)
    {
        arguments[i]->accept(*this);
        if (i < arguments.size() - 1)
        {
            json += ",";
        }
    }
    json += "]}";
}

void TreeVisitor::visit(const UnaryExpressionNode& node) const
{
    json += "{";
    json += "\"name\": \"Unary Expression\",";
    json += "\"attributes\": {\"operator\": \"" + node.getUnaryOperatorString() + "\", \"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getOperand().accept(*this);
    json += "]}";
}

void TreeVisitor::visit(const VariableReferenceNode& node) const
{
    json += "{";
    json += "\"name\": \"Variable Reference\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getIdentifier().accept(*this);
    
    const auto& indices = node.getIndices();
    if (!indices.empty())
    {
        json += "{";
        json += "\"name\": \"Indices\",";
        json += "\"children\": [";
        for (size_t i = 0; i < indices.size(); i++)
        {
            indices[i]->accept(*this);
            if (i < indices.size() - 1)
            {
                json += ",";
            }
        }
        json += "]}";
    }
    json += "]}";
}

void TreeVisitor::visit(const CharLiteralNode& node) const
{
    json += "{";
    json += "\"name\": \"Char Literal\",";
    json += "\"attributes\": {\"value\": " + std::to_string(node.getValue()) + ", \"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "}";
    json += "}";
}

void TreeVisitor::visit(const IntegerLiteralNode& node) const
{
    json += "{";
    json += "\"name\": \"Integer Literal\",";
    json += "\"attributes\": {\"value\": " + std::to_string(node.getValue()) + ", \"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "}";
    json += "}";
}

void TreeVisitor::visit(const FloatLiteralNode& node) const
{
    json += "{";
    json += "\"name\": \"Float Literal\",";
    json += "\"attributes\": {\"value\": " + std::to_string(node.getValue()) + ", \"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "}";
    json += "}";
}

void TreeVisitor::visit(const StringLiteralNode& node) const
{
    json += "{";
    json += "\"name\": \"String Literal\",";
    json += "\"attributes\": {\"value\": " + node.getValue() + ", \"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "}";
    json += "}";
}

void TreeVisitor::visit(const ReturnNode& node) const
{
    json += "{";
    json += "\"name\": \"Return\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getExpression().accept(*this);
    json += "]}";
}

void TreeVisitor::visit(const FunctionDeclarationNode& node) const
{
    json += "{";
    json += "\"name\": \"Function Declaration\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getIdentifier().accept(*this);
    json += ",";
    node.getReturnType().accept(*this);
    json += ",";
    
    const auto& parameters = node.getParameters();
    for (size_t i = 0; i < parameters.size(); i++)
    {
        parameters[i]->accept(*this);
        if (i < parameters.size() - 1)
        {
            json += ",";
        }
    }
    json += "]}";
}

void TreeVisitor::visit(const AssignmentStatementNode& node) const
{
    json += "{";
    json += "\"name\": \"Assignment Statement\",";
    if (node.getDereferenceLevel() > 0) json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + ",";
    else json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn());

    if (node.getDereferenceLevel() > 0)
    {
        json += "\"value\": \"" + std::to_string(node.getDereferenceLevel()) + "\"";
    }
    json += "},";
    json += "\"children\": [";
    node.getVarRef().accept(*this);
    json += ",";
    node.getValue().accept(*this);
    json += "]}";
}

void TreeVisitor::visit(const VariableDeclarationNode& node) const
{
    json += "{";
    json += "\"name\": \"Variable Declaration\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getType().accept(*this);
    json += ",";
    node.getIdentifier().accept(*this);
    if (!node.getArraySpecifiers().empty())
    {
        json += ",";
        const auto& specifiers = node.getArraySpecifiers();
        for (size_t i = 0; i < specifiers.size(); i++)
        {
            specifiers[i]->accept(*this);
            if (i < specifiers.size() - 1)
            {
                json += ","; 
            }
        }
    }
    json += "]}";
}

void TreeVisitor::visit(const FunctionCallStatementNode& node) const
{
    json += "{";
    json += "\"name\": \"Function Call Statement\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getIdentifier().accept(*this);
    const auto& arguments = node.getArguments();
    if (arguments.size() > 0) json += ",";  // comma for the identifier
    for (size_t i = 0; i < arguments.size(); i++)
    {
        arguments[i]->accept(*this);
        if (i < arguments.size() - 1)
        {
            json += ",";
        }
    }
    json += "]}";
}

void TreeVisitor::visit(const ForNode& node) const
{
    json += "{";
    json += "\"name\": \"For Statement\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getInit().accept(*this);
    json += ",";
    node.getCondition().accept(*this);
    json += ",";
    node.getIncrement().accept(*this);
    json += ",";
    
    json += "{";
    json += "\"name\": \"Body\",";
    json += "\"children\": [";
    const auto& statements = node.getBody();
    for (size_t i = 0; i < statements.size(); i++)
    {
        statements[i]->accept(*this);
        if (i < statements.size() - 1)
        {
            json += ",";
        }
    }
    json += "]}";
    
    json += "]}";
}

// TODO: Make else if/else nodes actual nodes, instead of just getting their children
void TreeVisitor::visit(const IfNode& node) const
{
    json += "{";
    json += "\"name\": \"If Statement\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getCondition().accept(*this);
    json += ",";
    node.getThenBlock().accept(*this);

    const auto& elseIfNodes = node.getElseIfBlocks();
    if (elseIfNodes.size() > 0) json += ",";
    for (size_t i = 0; i < elseIfNodes.size(); i++)
    {
        elseIfNodes[i].first->accept(*this);
        json += ",";
        elseIfNodes[i].second->accept(*this);
    }
    if (node.getElseBlock())
    {
        json += ",";
        node.getElseBlock()->accept(*this);
    }
    json += "]}";
}

void TreeVisitor::visit(const WhileNode& node) const
{
    json += "{";
    json += "\"name\": \"While Statement\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getCondition().accept(*this);
    json += ",";
    node.getBody().accept(*this);
    json += "]}";
}

void TreeVisitor::visit(const ArraySpecifierNode& node) const
{
    json += "{";
    json += "\"name\": \"Array Specifier\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    if (node.hasSize())
    {
        node.getSize().accept(*this);
    }
    json += "]}";
}

void TreeVisitor::visit(const ArrayInitializerNode& node) const
{
    json += "{";
    json += "\"name\": \"Array Initializer\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    const auto& values = node.getElements();
    for (size_t i = 0; i < values.size(); i++)
    {
        values[i]->accept(*this);
        if (i < values.size() - 1)
        {
            json += ",";
        }
    }
    json += "]}";
}

std::string TreeVisitor::getJson() const
{
    return json;
}

// Empty functions. should probably remove them from the parent abstract virtual class or whatever its called
void TreeVisitor::visit(const ExpressionNode& node) const {}

void TreeVisitor::visit(const LiteralNode& node) const {}

void TreeVisitor::visit(const StatementNode& node) const {}

void TreeVisitor::visit(const VariableDefinitionNode& node) const
{
    json += "{";
    json += "\"name\": \"Variable Definition\",";
    json += "\"attributes\": {\"line\": " + std::to_string(node.getLine()) + ", \"column\": " + std::to_string(node.getColumn()) + "},";
    json += "\"children\": [";
    node.getType().accept(*this);
    json += ",";
    node.getIdentifier().accept(*this);
    json += ",";
    node.getInit().accept(*this);
    json += "]}";
}