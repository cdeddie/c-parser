#pragma once

#include "parser/Node.hpp"
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
    
    Token peekToken();
    void advance();
    void expect(TokenType type);

    Environment env;

// Parse methods for each node
public:
    std::unique_ptr<ProgramNode> parseProgram();
    std::unique_ptr<FunctionDefinitionNode> parseFunctionDefinition();
    std::unique_ptr<TypeNode> parseType();
    std::unique_ptr<IdentifierNode> parseIdentifier();
    std::vector<std::unique_ptr<ParameterNode>> parseParameters(); // should this be vector return type?
    std::unique_ptr<BlockNode> parseBlock();
    std::unique_ptr<DeclarationNode> parseDeclaration();

    // Expressions
    std::unique_ptr<ExpressionNode> parseExpression();
    std::unique_ptr<FunctionCallNode> parseFunctionCall();
    std::unique_ptr<UnaryExpressionNode> parseUnaryExpression();
    std::unique_ptr<BinaryExpressionNode> parseBinaryExpression();
    std::unique_ptr<VariableReferenceNode> parseVariableReference();
    
    std::unique_ptr<LiteralNode> parseLiteral();
    std::unique_ptr<IntegerLiteralNode> parseIntegerLiteral();
    std::unique_ptr<FloatLiteralNode> parseFloatLiteral();
    std::unique_ptr<StringLiteralNode> parseStringLiteral();
    std::unique_ptr<CharLiteralNode> parseCharLiteral();

    // Statements
    std::unique_ptr<StatementNode> parseStatement();
    std::unique_ptr<ReturnNode> parseReturn();
    /*
    std::unique_ptr<AssignmentNode> parseAssignment();
    std::unique_ptr<IfNode> parseIf();
    std::unique_ptr<WhileNode> parseWhile();
    std::unique_ptr<ReturnNode> parseReturn();
    */
};