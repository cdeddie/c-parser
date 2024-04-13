#include "parser/HTMLVisitor.hpp"

void HTMLVisitor::visit(const BlockNode& node) const
{
    html += "<li data-type=\"BlockNode\"><span>Block</span>";
    html += "<ul id=\"children\">";
    for (const auto& statement : node.getStatements()) 
    {
        statement->accept(*this);
    }
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const FunctionDefinitionNode& node) const
{
    html += "<li data-type=\"FunctionDefinitionNode\"><span>Function Definition</span>";
    html += "<ul id=\"children\">";
    node.getIdentifier().accept(*this);
    node.getReturnType().accept(*this);

    for (const auto& parameter : node.getParameters()) 
    {
        parameter->accept(*this);
    }

    node.getBlock().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const IdentifierNode& node) const
{   
    html += "<li data-type=\"IdentifierNode\" data-name=\"" + node.getName() + "\"><span>Identifier</span></li>";
}

void HTMLVisitor::visit(const ParameterNode& node) const
{
    html += "<li data-type=\"ParameterNode\"><span>Parameter</span>";
    html += "<ul id=\"children\">";
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const ProgramNode& node) const
{
    html += "<li data-type=\"ProgramNode\"><span>Program</span>";
    html += "<ul id=\"children\">";
    for (const auto& statement : node.getStatements()) 
    { 
        statement->accept(*this);
    }
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const TypeNode& node) const
{
    html += "<li data-type=\"TypeNode\" data-datatype=\"" + node.getType() + "\"";
    if (node.getPointerLevel() > 0)
    {
        html += " data-pointerlevel=\"" + std::to_string(node.getPointerLevel()) + "\"";
    }
    html += "><span>Type</span></li>";
}

void HTMLVisitor::visit(const BinaryExpressionNode& node) const
{
    html += "<li data-type=\"BinaryExpressionNode\"><span>Binary Expression</span>";
    html += "<ul id=\"children\">";
    node.getLeft().accept(*this);
    html += "<li data-type=\"Operator\"><span>Operator: " + node.getBinaryOperatorString() + "</span></li>";
    node.getRight().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const ExpressionNode& node) const
{
    // Empty parent
}

void HTMLVisitor::visit(const FunctionCallExpressionNode& node) const
{
    html += "<li data-type=\"FunctionCallExpressionNode\"><span>Function Call Expression</span>";
    html += "<ul id=\"children\">";
    node.getIdentifier().accept(*this);
    for (const auto& argument : node.getArguments()) 
    {
        argument->accept(*this);
    }
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const UnaryExpressionNode& node) const
{
    html += "<li data-type=\"UnaryExpressionNode\"><span>Unary Expression</span>";
    html += "<ul id=\"children\">";
    node.getOperand().accept(*this);
    html += "<li data-type=\"Operator\"><span>" + node.getUnaryOperatorString() + "</span></li>";
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const VariableReferenceNode& node) const
{
    html += "<li data-type=\"VariableReferenceNode\"><span>Variable Reference</span>";
    html += "<ul id=\"children\">";
    node.getIdentifier().accept(*this);
    const auto& indices = node.getIndices();
    if (!indices.empty())
    {
        html += "<li data-type=\"Indices\"><span>Indices</span>";
        html += "<ul id=\"children\">";
        for (const auto& index : indices)
            index->accept(*this);
        html += "</ul>";
        html += "</li>";
    }
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const CharLiteralNode& node) const
{
    html += "<li data-type=\"CharLiteralNode\" data-value=\"" + std::string(1, node.getValue()) + "\"><span>Char Literal</span></li>";
}

void HTMLVisitor::visit(const FloatLiteralNode& node) const
{
    html += "<li data-type=\"FloatLiteralNode\" data-value=\"" + std::to_string(node.getValue()) + "\"><span>Float Literal</span></li>";
}

void HTMLVisitor::visit(const IntegerLiteralNode& node) const
{
    html += "<li data-type=\"IntegerLiteralNode\" data-value=\"" + std::to_string(node.getValue()) + "\"><span>Integer Literal</span></li>";
}

void HTMLVisitor::visit(const LiteralNode& node) const
{
    // Empty implementation
}

void HTMLVisitor::visit(const StringLiteralNode& node) const
{
    html += "<li data-type=\"StringLiteralNode\" data-value=\"" + node.getValue() + "\"><span>String Literal</span></li>";
}

void HTMLVisitor::visit(const ReturnNode& node) const
{
    html += "<li data-type=\"ReturnNode\"><span>Return</span>";
    html += "<ul id=\"children\">";
    node.getExpression().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const StatementNode& node) const
{
    // Empty implementation
}

void HTMLVisitor::visit(const FunctionDeclarationNode& node) const
{
    html += "<li data-type=\"FunctionDeclarationNode\"><span>Function Declaration</span>";
    html += "<ul id=\"children\">";
    node.getIdentifier().accept(*this);
    node.getReturnType().accept(*this);
    
    for (const auto& parameter : node.getParameters()) 
    {
        parameter->accept(*this);
    }
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const AssignmentStatementNode& node) const
{
    html += "<li data-type=\"AssignmentStatementNode\"";
    if (node.getDereferenceLevel() > 0)
    {
        html += " data-dereferencelevel=\"" + std::to_string(node.getDereferenceLevel()) + "\"";
    }
    html += "><span>Assignment Statement</span>";
    html += "<ul id=\"children\">";
    node.getVarRef().accept(*this);
    node.getValue().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const VariableDeclarationNode& node) const
{
    html += "<li data-type=\"VariableDeclarationNode\"><span>Variable Declaration</span>";
    html += "<ul id=\"children\">";
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);
    const auto& arraySpecifiers = node.getArraySpecifiers();
    if (!arraySpecifiers.empty())
    {
        html += "<li data-type=\"ArraySpecifiers\"><span>Array Specifiers</span>";
        html += "<ul id=\"children\">";
        for (const auto& specifier : arraySpecifiers)
            specifier->accept(*this);
        html += "</ul>";
        html += "</li>";
    }
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const VariableDefinitionNode& node) const
{
    html += "<li data-type=\"VariableDefinitionNode\"><span>Variable Definition</span>";
    html += "<ul id=\"children\">";
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);

    if (!node.getArraySpecifiers().empty())
    {
        html += "<li data-type=\"ArraySpecifiers\"><span>Array Specifiers</span>";
        html += "<ul id=\"children\">";
        for (const auto& specifier : node.getArraySpecifiers())
            specifier->accept(*this);
        html += "</ul>";
        html += "</li>";
    }
    node.getInit().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const FunctionCallStatementNode& node) const
{
    html += "<li data-type=\"FunctionCallStatementNode\"><span>Function Call Statement</span>";
    html += "<ul id=\"children\">";
    node.getIdentifier().accept(*this);

    for (const auto& argument : node.getArguments()) 
    {
        argument->accept(*this);
    }
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const ForNode& node) const
{
    html += "<li data-type=\"ForNode\"><span>For</span>";
    html += "<ul id=\"children\">";
    node.getInit().accept(*this);
    node.getCondition().accept(*this);
    node.getIncrement().accept(*this);

    html += "<li data-type=\"Body\"><span>Body</span>";
    html += "<ul id=\"children\">";
    for (const auto& statement : node.getBody()) 
    {
        statement->accept(*this);
    }
    html += "</ul>";
    html += "</li>";

    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const IfNode& node) const
{
    html += "<li data-type=\"IfNode\"><span>If</span>";
    html += "<ul id=\"children\">";

    html += "<li data-type=\"Condition\"><span>Condition</span>";
    node.getCondition().accept(*this);
    html += "</li>";

    html += "<li data-type=\"ThenBlock\"><span>Then Block</span>";
    node.getThenBlock().accept(*this);
    html += "</li>";

    const auto& elseIfBlocks = node.getElseIfBlocks();
    for (const auto& elseIf : elseIfBlocks)
    {
        html += "<li data-type=\"ElseIfNode\"><span>Else If</span>";
        html += "<ul id=\"children\">";

        html += "<li data-type=\"Condition\"><span>Condition</span>";
        elseIf.first->accept(*this);
        html += "</li>";

        html += "<li data-type=\"Block\"><span>Block</span>";
        elseIf.second->accept(*this);
        html += "</li>";

        html += "</ul>";
        html += "</li>";
    }

    const auto& elseBlock = node.getElseBlock();
    if (elseBlock)
    {
        html += "<li data-type=\"ElseBlock\"><span>Else Block</span>";
        elseBlock->accept(*this);
        html += "</li>";
    }

    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const WhileNode& node) const
{
    html += "<li data-type=\"WhileNode\"><span>While</span>";
    html += "<ul id=\"children\">";
    node.getCondition().accept(*this);
    node.getBody().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const ArraySpecifierNode& node) const
{
    html += "<li data-type=\"ArraySpecifierNode\"><span>Array Specifier</span>";
    html += "<ul id=\"children\">";
    if (node.hasSize())
        node.getSize().accept(*this);
    else
        html += "<li data-type=\"Size\"><span>unspecified</span></li>";
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const ArrayInitializerNode& node) const
{
    html += "<li data-type=\"ArrayInitializerNode\"><span>Array Initializer</span>";
    html += "<ul id=\"children\">";
    for (const auto& element : node.getElements())
        element->accept(*this);
    html += "</ul>";
    html += "</li>";
}

std::string HTMLVisitor::getHTML() const
{
    return html;
}