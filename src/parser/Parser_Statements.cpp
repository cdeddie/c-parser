#include "parser/Parser.hpp"

std::unique_ptr<StatementNode> Parser::parseStatement()
{
    switch (currentToken.getType())
    {
        case TokenType::Return:
            return parseReturn();
        case TokenType::Type:
            if (peekToken().getType() == TokenType::Identifier)
            {
                if (peekToken(2).getType() == TokenType::Semicolon)
                {
                    return parseVariableDeclaration();
                }
                else if (peekToken(2).getType() == TokenType::Assignment)
                {
                    return parseVariableDefinition();
                }
            }
        default:
            return nullptr;
    }
}

std::unique_ptr<VariableDeclarationNode> Parser::parseVariableDeclaration()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    auto typeNode = parseType();
    auto identifierNode = parseIdentifier();
    expect(TokenType::Semicolon);

    return std::make_unique<VariableDeclarationNode>(
        std::move(typeNode),
        std::move(identifierNode),
        startLine,
        startColumn
    );
}

std::unique_ptr<VariableDefinitionNode> Parser::parseVariableDefinition()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    auto typeNode = parseType();
    auto identifierNode = parseIdentifier();
    expect(TokenType::Assignment);
    auto expression = parseExpression();
    expect(TokenType::Semicolon);

    return std::make_unique<VariableDefinitionNode>(
        std::move(typeNode),
        std::move(identifierNode),
        std::move(expression),
        startLine,
        startColumn
    );
}

std::unique_ptr<ReturnNode> Parser::parseReturn()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    expect(TokenType::Return);
    auto expression = parseExpression();
    expect(TokenType::Semicolon);
    return std::make_unique<ReturnNode>(std::move(expression), startLine, startColumn);
}