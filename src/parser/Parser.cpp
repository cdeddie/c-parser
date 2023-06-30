#include "parser/Parser.hpp"

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.nextToken())
{
	
}

void Parser::advance()
{
    currentToken = lexer.nextToken();
}

void Parser::expect(TokenType type)
{
    if (currentToken.getType() == type)
    {
        advance();
    }
    else
    {
        throw std::runtime_error("Unexpected token: ");
    }
}

std::unique_ptr<AST> Parser::parse()
{
    return nullptr;
}

std::unique_ptr<ProgramNode> Parser::parseProgram()
{
    auto programNode = std::make_unique<ProgramNode>();
    while (currentToken.getType() != TokenType::EndOfFile)
    {
        programNode->addChild(parseFunctionDefinition());
    }
    return programNode;
}

std::unique_ptr<FunctionDefinitionNode> Parser::parseFunctionDefinition()
{
    auto functionNode = std::make_unique<FunctionDefinitionNode>();

    functionNode->setReturnType(parseType());
    functionNode->setIdentifier(parseIdentifier());
    functionNode->setParameters(parseParameters());
    functionNode->setBlock(parseBlock());

    advance();
    return functionNode;
}

std::unique_ptr<ExpressionNode> Parser::parseExpression()
{
    return nullptr;
}

std::unique_ptr<TypeNode> Parser::parseType()
{
    if (currentToken.getType() != TokenType::Type)
    {
        throw std::runtime_error("Expected a type");
    }
    auto typeNode = std::make_unique<TypeNode>(currentToken.getValue());
    advance();
    return typeNode;
}

std::unique_ptr<IdentifierNode> Parser::parseIdentifier()
{
    if (currentToken.getType() != TokenType::Identifier)
    {
        throw std::runtime_error("Expected an identifier ");
    }
    auto identifierNode = std::make_unique<IdentifierNode>(currentToken.getValue());
    advance();
    return identifierNode;
}

std::vector<std::unique_ptr<ParameterNode>> Parser::parseParameters()
{
    return std::vector<std::unique_ptr<ParameterNode>>();
}

std::unique_ptr<BlockNode> Parser::parseBlock()
{
    return nullptr;
}

