#pragma once

#include "parser/Node.hpp"
#include "parser/AST/ProgramNode.hpp"
#include "parser/AST.hpp"
#include "parser/Environment.hpp"
#include "lexer/Lexer.hpp"

#include "parser/ParserIncludes.hpp"

class Parser
{
public:
    explicit Parser(Lexer& lexer);
    std::unique_ptr<AST> parse();

private:
    Lexer& lexer;
    Token currentToken;

    void advance();
    void expect(TokenType type);

// Parse methods for each node
public:
    std::unique_ptr<ProgramNode> parseProgram();
    std::unique_ptr<FunctionDefinitionNode> parseFunctionDefinition();
    std::unique_ptr<ExpressionNode> parseExpression();
    std::unique_ptr<TypeNode> parseType();
    std::unique_ptr<IdentifierNode> parseIdentifier();
    std::vector<std::unique_ptr<ParameterNode>> parseParameters(); // should this be vector return type?
    std::unique_ptr<BlockNode> parseBlock();
    std::unique_ptr<StatementNode> parseStatement();
    std::unique_ptr<DeclarationNode> parseDeclaration();
    std::unique_ptr<FunctionCallNode> parseFunctionCall();
    std::unique_ptr<UnaryExpressionNode> parseUnaryExpression();
    std::unique_ptr<BinaryExpressionNode> parseBinaryExpression();
    /*
    std::unique_ptr<AssignmentNode> parseAssignment();
    std::unique_ptr<IfNode> parseIf();
    std::unique_ptr<WhileNode> parseWhile();
    std::unique_ptr<ReturnNode> parseReturn();
    std::unique_ptr<LiteralNode> parseLiteral();
    std::unique_ptr<NumberNode> parseNumber();
    std::unique_ptr<StringNode> parseString();
    std::unique_ptr<BoolNode> parseBool();
    std::unique_ptr<NullNode> parseNull();

    std::unique_ptr<IdentifierNode> parseIdentifierExpression();
    std::unique_ptr<IdentifierNode> parseIdentifierStatement();
    std::unique_ptr<IdentifierNode> parseIdentifierDeclaration();
    std::unique_ptr<IdentifierNode> parseIdentifierFunctionCall();
    std::unique_ptr<IdentifierNode> parseIdentifierReturn();
    std::unique_ptr<IdentifierNode> parseIdentifierIf();
    std::unique_ptr<IdentifierNode> parseIdentifierWhile();
    std::unique_ptr<IdentifierNode> parseIdentifierBlock();
    std::unique_ptr<IdentifierNode> parseIdentifierType();
    std::unique_ptr<IdentifierNode> parseIdentifierLiteral();
    std::unique_ptr<IdentifierNode> parseIdentifierNumber();
    std::unique_ptr<IdentifierNode> parseIdentifierString();
    std::unique_ptr<IdentifierNode> parseIdentifierBool();
    std::unique_ptr<IdentifierNode> parseIdentifierNull();
    */
};