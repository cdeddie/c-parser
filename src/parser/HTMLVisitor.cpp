#include "parser/HTMLVisitor.hpp"

void HTMLVisitor::visit(const BlockNode& node) const
{
    html += "<li data-type=\"BlockNode\"><div class=\"tooltip\"><span>Block</span></div>";
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
    html += "<li data-type=\"FunctionDefinitionNode\"><div class=\"tooltip\"><span>Function Definition</span></div>";
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
    html += "<li data-type=\"IdentifierNode\" data-name=\"" + node.getName() + "\"><div class=\"tooltip\"><span>Identifier</span><span class=\"tooltiptext\">Name: " + node.getName() + "</span></div></li>";
}

void HTMLVisitor::visit(const ParameterNode& node) const
{
    html += "<li data-type=\"ParameterNode\"><div class=\"tooltip\"><span>Parameter</span></div>";
    html += "<ul id=\"children\">";
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const ProgramNode& node) const
{
    html += "<li data-type=\"ProgramNode\"><div class=\"tooltip\"><span>Program</span></div>";
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
    std::string tooltipText = "Type: " + node.getType();
    if (node.getPointerLevel() > 0)
    {
        tooltipText += " (Pointer Level: " + std::to_string(node.getPointerLevel()) + ")";
    }

    html += "<li data-type=\"TypeNode\" data-datatype=\"" + node.getType() + "\"";
    if (node.getPointerLevel() > 0)
    {
        html += " data-pointerlevel=\"" + std::to_string(node.getPointerLevel()) + "\"";
    }
    html += "><div class=\"tooltip\"><span>Type</span><span class=\"tooltiptext\">" + tooltipText + "</span></div></li>";
}

void HTMLVisitor::visit(const BinaryExpressionNode& node) const
{
    html += "<li data-type=\"BinaryExpressionNode\"><div class=\"tooltip\"><span>Binary Expression</span><span class=\"tooltiptext\">Operator: " + node.getBinaryOperatorString() + "</span></div>";
    html += "<ul id=\"children\">";
    node.getLeft().accept(*this);
    html += "<li data-type=\"Operator\"><div class=\"tooltip\"><span>Operator: " + node.getBinaryOperatorString() + "</span></div></li>";
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
    html += "<li data-type=\"FunctionCallExpressionNode\"><div class=\"tooltip\"><span>Function Call Expression</span></div>";
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
    html += "<li data-type=\"UnaryExpressionNode\"><div class=\"tooltip\"><span>Unary Expression</span><span class=\"tooltiptext\">Operator: " + node.getUnaryOperatorString() + "</span></div>";
    html += "<ul id=\"children\">";
    node.getOperand().accept(*this);
    html += "<li data-type=\"Operator\"><div class=\"tooltip\"><span>" + node.getUnaryOperatorString() + "</span></div></li>";
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const VariableReferenceNode& node) const
{
    html += "<li data-type=\"VariableReferenceNode\"><div class=\"tooltip\"><span>Variable Reference</span></div>";
    html += "<ul id=\"children\">";
    node.getIdentifier().accept(*this);
    const auto& indices = node.getIndices();
    if (!indices.empty())
    {
        html += "<li data-type=\"Indices\"><div class=\"tooltip\"><span>Indices</span></div>";
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
    html += "<li data-type=\"CharLiteralNode\" data-value=\"" + std::string(1, node.getValue()) + "\"><div class=\"tooltip\"><span>Char Literal</span><span class=\"tooltiptext\">Value: " + std::string(1, node.getValue()) + "</span></div></li>";
}

void HTMLVisitor::visit(const FloatLiteralNode& node) const
{
    html += "<li data-type=\"FloatLiteralNode\" data-value=\"" + std::to_string(node.getValue()) + "\"><div class=\"tooltip\"><span>Float Literal</span><span class=\"tooltiptext\">Value: " + std::to_string(node.getValue()) + "</span></div></li>";
}

void HTMLVisitor::visit(const IntegerLiteralNode& node) const
{
    html += "<li data-type=\"IntegerLiteralNode\" data-value=\"" + std::to_string(node.getValue()) + "\"><div class=\"tooltip\"><span>Integer Literal</span><span class=\"tooltiptext\">Value: " + std::to_string(node.getValue()) + "</span></div></li>";
}

void HTMLVisitor::visit(const LiteralNode& node) const
{
    // Empty implementation
}

void HTMLVisitor::visit(const StringLiteralNode& node) const
{
    html += "<li data-type=\"StringLiteralNode\" data-value=\"" + node.getValue() + "\"><div class=\"tooltip\"><span>String Literal</span><span class=\"tooltiptext\">Value: " + node.getValue() + "</span></div></li>";
}

void HTMLVisitor::visit(const ReturnNode& node) const
{
    html += "<li data-type=\"ReturnNode\"><div class=\"tooltip\"><span>Return</span></div>";
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
    html += "<li data-type=\"FunctionDeclarationNode\"><div class=\"tooltip\"><span>Function Declaration</span></div>";
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
    std::string tooltipText = "Assignment Statement";
    if (node.getDereferenceLevel() > 0)
    {
        tooltipText += " (Dereference Level: " + std::to_string(node.getDereferenceLevel()) + ")";
    }

    html += "<li data-type=\"AssignmentStatementNode\"";
    if (node.getDereferenceLevel() > 0)
    {
        html += " data-dereferencelevel=\"" + std::to_string(node.getDereferenceLevel()) + "\"";
    }
    html += "><div class=\"tooltip\"><span>Assignment Statement</span><span class=\"tooltiptext\">" + tooltipText + "</span></div>";
    html += "<ul id=\"children\">";
    node.getVarRef().accept(*this);
    node.getValue().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const VariableDeclarationNode& node) const
{
    html += "<li data-type=\"VariableDeclarationNode\"><div class=\"tooltip\"><span>Variable Declaration</span></div>";
    html += "<ul id=\"children\">";
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);
    const auto& arraySpecifiers = node.getArraySpecifiers();
    if (!arraySpecifiers.empty())
    {
        html += "<li data-type=\"ArraySpecifiers\"><div class=\"tooltip\"><span>Array Specifiers</span></div>";
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
    html += "<li data-type=\"VariableDefinitionNode\"><div class=\"tooltip\"><span>Variable Definition</span></div>";
    html += "<ul id=\"children\">";
    node.getType().accept(*this);
    node.getIdentifier().accept(*this);

    if (!node.getArraySpecifiers().empty())
    {
        html += "<li data-type=\"ArraySpecifiers\"><div class=\"tooltip\"><span>Array Specifiers</span></div>";
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
    html += "<li data-type=\"FunctionCallStatementNode\"><div class=\"tooltip\"><span>Function Call Statement</span></div>";
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
    html += "<li data-type=\"ForNode\"><div class=\"tooltip\"><span>For</span></div>";
    html += "<ul id=\"children\">";
    node.getInit().accept(*this);
    node.getCondition().accept(*this);
    node.getIncrement().accept(*this);

    html += "<li data-type=\"Body\"><div class=\"tooltip\"><span>Body</span></div>";
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
    html += "<li data-type=\"IfNode\"><div class=\"tooltip\"><span>If</span></div>";
    html += "<ul id=\"children\">";

    html += "<li data-type=\"Condition\"><div class=\"tooltip\"><span>Condition</span></div>";
    node.getCondition().accept(*this);
    html += "</li>";

    html += "<li data-type=\"ThenBlock\"><div class=\"tooltip\"><span>Then Block</span></div>";
    node.getThenBlock().accept(*this);
    html += "</li>";

    const auto& elseIfBlocks = node.getElseIfBlocks();
    for (const auto& elseIf : elseIfBlocks)
    {
        html += "<li data-type=\"ElseIfNode\"><div class=\"tooltip\"><span>Else If</span></div>";
        html += "<ul id=\"children\">";

        html += "<li data-type=\"Condition\"><div class=\"tooltip\"><span>Condition</span></div>";
        elseIf.first->accept(*this);
        html += "</li>";

        html += "<li data-type=\"Block\"><div class=\"tooltip\"><span>Block</span></div>";
        elseIf.second->accept(*this);
        html += "</li>";

        html += "</ul>";
        html += "</li>";
    }

    const auto& elseBlock = node.getElseBlock();
    if (elseBlock)
    {
        html += "<li data-type=\"ElseBlock\"><div class=\"tooltip\"><span>Else Block</span></div>";
        elseBlock->accept(*this);
        html += "</li>";
    }

    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const WhileNode& node) const
{
    html += "<li data-type=\"WhileNode\"><div class=\"tooltip\"><span>While</span></div>";
    html += "<ul id=\"children\">";
    node.getCondition().accept(*this);
    node.getBody().accept(*this);
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const ArraySpecifierNode& node) const
{
    html += "<li data-type=\"ArraySpecifierNode\"><div class=\"tooltip\"><span>Array Specifier</span></div>";
    html += "<ul id=\"children\">";
    if (node.hasSize())
        node.getSize().accept(*this);
    else
        html += "<li data-type=\"Size\"><div class=\"tooltip\"><span>unspecified</span></div></li>";
    html += "</ul>";
    html += "</li>";
}

void HTMLVisitor::visit(const ArrayInitializerNode& node) const
{
    html += "<li data-type=\"ArrayInitializerNode\"><div class=\"tooltip\"><span>Array Initializer</span></div>";
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