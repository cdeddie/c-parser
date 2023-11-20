#include "parser/JsonExportVisitor.hpp"

using json = nlohmann::json;

json JsonExportVisitor::toJson(const ProgramNode& node)
{
    node.accept(*this);
    return result;
}

// Creates a temp JSON array to store the JSON of each node, iterates over child nodes add the result of each to array
// polymorphism does not work with data structures of containers (unique_ptr) ??
template <typename T>
json JsonExportVisitor::addChildNodes(const std::vector<std::unique_ptr<T>>& children) const
{
    json childrenJson = json::array();
    for (const auto& child : children)
    {
        static_cast<const Node*>(child.get())->accept(*this);
        childrenJson.push_back(result);
    }
    return childrenJson;
}

// Construct JSON for current node -> visit child nodes ->
// store their JSON in seperate variables -> combine into parents JSON

// -------------------------- Base AST Nodes --------------------------

void JsonExportVisitor::visit(const BlockNode& node) const
{
    json j = {
        {"type", "BlockNode"},
        {"statements", addChildNodes(node.getStatements())}
    };
    result = j;
}

void JsonExportVisitor::visit(const FunctionDefinitionNode& node) const
{
    node.getIdentifier().accept(*this);
    json identifierJson = result;

    node.getReturnType().accept(*this);
    json returnTypeJson = result;

    json parametersJson = addChildNodes(node.getParameters());
    node.getBlock().accept(*this);
    json bodyJson = result;

    json j = {
        {"type", "FunctionDefinitionNode"},
        {"identifier", identifierJson},
        {"returnType", returnTypeJson},
        {"parameters", parametersJson},
        {"body", bodyJson}
    };
    result = j;
}


void JsonExportVisitor::visit(const IdentifierNode& node) const
{
    json j = {
        {"type", "IdentifierNode"},
        {"name", node.getName()}
    };
    result = j;
}

void JsonExportVisitor::visit(const ParameterNode& node) const
{
    node.getType().accept(*this);
    json typeJson = result;

    node.getIdentifier().accept(*this);
    json identifierJson = result;

    json j = {
        {"type", "ParameterNode"},
        {"dataType", typeJson},
        {"identifier", identifierJson}
    };
    result = j;
}


void JsonExportVisitor::visit(const ProgramNode& node) const
{
    json j = {
        {"type", "ProgramNode"},
        {"statements", addChildNodes(node.getStatements())}
    };
    result = j;
}

void JsonExportVisitor::visit(const TypeNode& node) const
{
    json j = {
        {"type", "TypeNode"},
        {"dataType", node.getType()}
    };
    if (node.getPointerLevel() > 0) {
        j["pointerLevel"] = node.getPointerLevel();
    }
    result = j;
}

// -------------------------- Expression Nodes --------------------------

void JsonExportVisitor::visit(const BinaryExpressionNode& node) const
{
    node.getLeft().accept(*this);
    json leftJson = result;

    node.getRight().accept(*this);
    json rightJson = result;

    json j = {
        {"type", "BinaryExpressionNode"},
        {"operator", node.getBinaryOperatorString()},
        {"left", leftJson},
        {"right", rightJson}
    };

    result = j;
}

void JsonExportVisitor::visit(const ExpressionNode& node) const
{
    // Empty parent class
    result = json{{"error", "Unexpected ExpressionNode"}};
}

void JsonExportVisitor::visit(const FunctionCallExpressionNode& node) const
{
    node.getIdentifier().accept(*this);
    json identifierJson = result;

    json argumentsJson = addChildNodes(node.getArguments());

    json j = {
        {"type", "FunctionCallExpressionNode"},
        {"identifier", identifierJson},
        {"arguments", argumentsJson}
    };

    result = j;
}

void JsonExportVisitor::visit(const UnaryExpressionNode& node) const
{
    node.getOperand().accept(*this);
    json operandJson = result;

    json j = {
        {"type", "UnaryExpressionNode"},
        {"operator", node.getUnaryOperatorString()},
        {"operand", operandJson}
    };

    result = j;
}

void JsonExportVisitor::visit(const VariableReferenceNode& node) const
{
    node.getIdentifier().accept(*this);
    json identifierJson = result;

    json indicesJson = json::array();
    for (const auto& index : node.getIndices()) {
        index->accept(*this);
        indicesJson.push_back(result);
    }

    json j = {
        {"type", "VariableReferenceNode"},
        {"identifier", identifierJson},
        {"indices", indicesJson}
    };

    result = j;
}

// -------------------------- Literal Nodes --------------------------

void JsonExportVisitor::visit(const CharLiteralNode& node) const
{
    json j;
    j["type"] = "CharLiteralNode";
    j["value"] = node.getValue();
    result = j;
}

void JsonExportVisitor::visit(const FloatLiteralNode& node) const
{
    json j;
    j["type"] = "FloatLiteralNode";
    j["value"] = node.getValue();
    result = j;
}

void JsonExportVisitor::visit(const IntegerLiteralNode& node) const
{
    json j;
    j["type"] = "IntegerLiteralNode";
    j["value"] = node.getValue();
    result = j;
}

void JsonExportVisitor::visit(const LiteralNode& node) const
{
    // Empty parent class
    result = json{{"error", "Unexpected LiteralNode"}};
}

void JsonExportVisitor::visit(const StringLiteralNode& node) const
{
    json j;
    j["type"] = "StringLiteralNode";
    j["value"] = node.getValue();
    result = j;
}

// -------------------------- Statement Nodes --------------------------

void JsonExportVisitor::visit(const ReturnNode& node) const
{
    node.getExpression().accept(*this);
    json j = {
        {"type", "ReturnNode"},
        {"expression", result}
    };
    result = j;
}

void JsonExportVisitor::visit(const StatementNode& node) const
{
    // Empty parent class
    result = json{{"error", "Unexpected StatementNode"}};
}

void JsonExportVisitor::visit(const FunctionDeclarationNode& node) const
{
    node.getIdentifier().accept(*this);
    json identifierJson = result;

    node.getReturnType().accept(*this);
    json returnTypeJson = result;

    json parametersJson = addChildNodes(node.getParameters());

    json j = {
        {"type", "FunctionDeclarationNode"},
        {"identifier", identifierJson},
        {"returnType", returnTypeJson},
        {"parameters", parametersJson}
    };
    result = j;
}

void JsonExportVisitor::visit(const AssignmentStatementNode& node) const
{
    node.getVarRef().accept(*this);
    json varRefJson = result;

    node.getValue().accept(*this);
    json valueJson = result;

    json j = {
        {"type", "AssignmentStatementNode"},
        {"dereferenceLevel", node.getDereferenceLevel()},
        {"variableReference", varRefJson},
        {"value", valueJson}
    };
    result = j;
}

void JsonExportVisitor::visit(const VariableDeclarationNode& node) const
{
    node.getType().accept(*this);
    json dataTypeJson = result;

    node.getIdentifier().accept(*this);
    json identifierJson = result;

    json arraySpecifiersJson = addChildNodes(node.getArraySpecifiers());

    json j = {
        {"type", "VariableDeclarationNode"},
        {"dataType", dataTypeJson},
        {"identifier", identifierJson},
        {"arraySpecifiers", arraySpecifiersJson}
    };
    result = j;
}

void JsonExportVisitor::visit(const VariableDefinitionNode& node) const
{
    node.getType().accept(*this);
    json dataTypeJson = result;

    node.getIdentifier().accept(*this);
    json identifierJson = result;

    json arraySpecifiersJson = addChildNodes(node.getArraySpecifiers());

    node.getInit().accept(*this);
    json initializerJson = result;

    json j = {
        {"type", "VariableDefinitionNode"},
        {"dataType", dataTypeJson},
        {"identifier", identifierJson},
        {"arraySpecifiers", arraySpecifiersJson},
        {"initializer", initializerJson}
    };
    result = j;
}

void JsonExportVisitor::visit(const FunctionCallStatementNode& node) const
{
    node.getIdentifier().accept(*this);
    json identifierJson = result;

    json argumentsJson = addChildNodes(node.getArguments());

    json j = {
        {"type", "FunctionCallStatementNode"},
        {"identifier", identifierJson},
        {"arguments", argumentsJson}
    };
    result = j;
}

void JsonExportVisitor::visit(const ForNode& node) const
{
    node.getInit().accept(*this);
    json initializerJson = result;

    node.getCondition().accept(*this);
    json conditionJson = result;

    node.getIncrement().accept(*this);
    json incrementJson = result;

    json bodyJson = addChildNodes(node.getBody());

    json j = {
        {"type", "ForNode"},
        {"initializer", initializerJson},
        {"condition", conditionJson},
        {"increment", incrementJson},
        {"body", bodyJson}
    };

    result = j;
}

void JsonExportVisitor::visit(const IfNode& node) const
{
    node.getCondition().accept(*this);
    json conditionJson = result;

    node.getThenBlock().accept(*this);
    json thenBlockJson = result;

    json elseIfBlocksJson = json::array();
    for (const auto& elseIf : node.getElseIfBlocks())
    {
        elseIf.first->accept(*this);
        json elseIfConditionJson = result;

        elseIf.second->accept(*this);
        json elseIfBlockJson = result;

        elseIfBlocksJson.push_back({{"condition", elseIfConditionJson}, {"block", elseIfBlockJson}});
    }

    json elseBlockJson;
    const auto& elseBlock = node.getElseBlock();
    if (elseBlock)
    {
        elseBlock->accept(*this);
        elseBlockJson = {{"elseBlock", result}};
    }

    json j = {
        {"type", "IfNode"},
        {"condition", conditionJson},
        {"thenBlock", thenBlockJson},
        {"elseIfBlocks", elseIfBlocksJson},
        {"elseBlock", elseBlockJson}
    };

    result = j;
}

void JsonExportVisitor::visit(const WhileNode& node) const
{
    node.getCondition().accept(*this);
    json conditionJson = result;

    node.getBody().accept(*this);
    json bodyJson = result;

    json j = {
        {"type", "WhileNode"},
        {"condition", conditionJson},
        {"body", bodyJson}
    };

    result = j;
}

// -------------------------- Declaration Nodes --------------------------

void JsonExportVisitor::visit(const ArraySpecifierNode& node) const
{
    json sizeJson;
    if (node.hasSize())
    {
        node.getSize().accept(*this);
        sizeJson = result;
    }
    else
    {
        sizeJson = "unspecified";
    }

    json j = {
        {"type", "ArraySpecifierNode"},
        {"size", sizeJson}
    };

    result = j;
}

void JsonExportVisitor::visit(const ArrayInitializerNode& node) const
{
    json elementsJson = addChildNodes(node.getElements());

    json j = {
        {"type", "ArrayInitializerNode"},
        {"elements", elementsJson}
    };

    result = j;
}
