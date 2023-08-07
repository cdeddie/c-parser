#pragma once

#include "parser/Node.hpp"
#include "parser/AST.hpp"
#include "parser/Environment.hpp"
#include "parser/ParserException.hpp"
#include "lexer/Lexer.hpp"

#include "parser/ParserIncludes.hpp"

#include <iostream>
#include <optional>
#include <map>

class Parser
{
public:
    explicit Parser(Lexer& lexer);
    std::unique_ptr<AST> parse();

    void printTokens(int n);

private:
    Lexer& lexer;
    Token currentToken;
    
    Token peekToken(int n) const;
    Token peekToken() const;
    void advance();
    void expect(TokenType type, std::optional<std::string> value = std::nullopt);

    Environment env; // Probably not needed

// Parse methods for each node
private:
    std::unique_ptr<ProgramNode> parseProgram();
    std::unique_ptr<TypeNode> parseType();
    std::unique_ptr<IdentifierNode> parseIdentifier();
    std::vector<std::unique_ptr<ParameterNode>> parseParameters();
    std::unique_ptr<BlockNode> parseBlock();

    std::unique_ptr<FunctionDefinitionNode> parseFunctionDefinition();
    std::unique_ptr<FunctionDeclarationNode> parseFunctionDeclaration();

    // Expressions
    std::unique_ptr<ExpressionNode> parseExpression();
    std::unique_ptr<ExpressionNode> parsePrimaryExpression();
    std::unique_ptr<FunctionCallExpressionNode> parseFunctionCallExpression();
    std::unique_ptr<UnaryExpressionNode> parseUnaryExpression();

    enum class UnaryOperatorNodeType { Prefix, Postfix, None };
    UnaryOperatorNodeType getUnaryOperatorNodeType(const Token& token);
    UnaryOperatorType tokenToUnaryOperatorType(const Token& token);

    bool isBinaryOperator(const Token& token);
    int getBinaryOperatorPrecendence(const Token& token);
    BinaryOperatorType tokenToBinaryOperatorType(const Token& token);
    std::unique_ptr<ExpressionNode> parseBinaryExpression(int exprPrec, std::unique_ptr<ExpressionNode> left);
    std::unique_ptr<VariableReferenceNode> parseVariableReference();
    
    std::unique_ptr<LiteralNode> parseLiteral();
    std::unique_ptr<IntegerLiteralNode> parseIntegerLiteral();
    std::unique_ptr<FloatLiteralNode> parseFloatLiteral();
    std::unique_ptr<StringLiteralNode> parseStringLiteral();
    std::unique_ptr<CharLiteralNode> parseCharLiteral();

    // Statements
    std::unique_ptr<StatementNode> parseStatement();
    std::unique_ptr<ReturnNode> parseReturn();
    std::unique_ptr<FunctionCallStatementNode> parseFunctionCallStatement();
    std::unique_ptr<ForNode> parseForStatement();
    std::unique_ptr<IfNode> parseIfStatement();
    std::unique_ptr<WhileNode> parseWhileStatement();
    
    std::unique_ptr<VariableDefinitionNode> parseVariableDefinition();
    std::unique_ptr<VariableDeclarationNode> parseVariableDeclaration();

};