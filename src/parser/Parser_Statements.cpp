#include "parser/Parser.hpp"

std::unique_ptr<StatementNode> Parser::parseStatement()
{
    switch (currentToken.getType())
    {
        case TokenType::Return:
            return parseReturn();
        default:
            return nullptr;
    }
}

std::unique_ptr<DeclarationNode> Parser::parseDeclaration()
{
    return nullptr;
}

std::unique_ptr<ReturnNode> Parser::parseReturn()
{
    expect(TokenType::Return);
    auto expression = parseExpression();
    expect(TokenType::Semicolon);
    return std::make_unique<ReturnNode>(std::move(expression));
}