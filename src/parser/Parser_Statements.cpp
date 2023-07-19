#include "parser/Parser.hpp"

std::unique_ptr<StatementNode> Parser::parseStatement()
{
    switch (currentToken.getType())
    {
        case TokenType::Identifier:
            if (peekToken().getType() == TokenType::OpenParen)
            {
                return parseFunctionCallStatement();
            }
        case TokenType::Keyword:
            if (currentToken.getValue() == "for")
                return parseForStatement();
            else if (currentToken.getValue() == "if")
                return parseIfStatement();
            else if (currentToken.getValue() == "while")
                return parseWhileStatement();
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
        case TokenType::Minus:
        case TokenType::Exclamation:
        case TokenType::Increment:
        case TokenType::Decrement:
        case TokenType::Ampersand:
        case TokenType::Asterisk:
            {
                auto unaryExpression = parseUnaryExpression();
                expect(TokenType::Semicolon);
                return unaryExpression;
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

std::unique_ptr<FunctionCallStatementNode> Parser::parseFunctionCallStatement()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    std::unique_ptr<IdentifierNode> identifier = parseIdentifier();
    expect(TokenType::OpenParen);
    std::vector<std::unique_ptr<ExpressionNode>> args;

    while (currentToken.getType() != TokenType::CloseParen)
    {
        args.push_back(parseExpression());
        if (currentToken.getType() == TokenType::Comma)
            advance();
    }

    expect(TokenType::CloseParen);
    expect(TokenType::Semicolon);
    
    return std::make_unique<FunctionCallStatementNode>(
        std::move(identifier), 
        std::move(args), 
        startLine, 
        startColumn
    );
}

std::unique_ptr<ForNode> Parser::parseForStatement()
{
    std::cout << "Recognized for statement\n";
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    expect(TokenType::Keyword, "for");
    expect(TokenType::OpenParen);

    auto init = parseStatement();

    auto condition = parseExpression();
    expect(TokenType::Semicolon);

    auto increment = parseExpression();
    expect(TokenType::CloseParen);

    std::vector<std::unique_ptr<StatementNode>> body;
    if (currentToken.getType() == TokenType::OpenBracket)
    {
        expect(TokenType::OpenBracket);
        while (currentToken.getType() != TokenType::CloseBracket)
        {
            body.push_back(parseStatement());
        }
        expect(TokenType::CloseBracket);
    }
    else 
    {
        body.push_back(parseStatement());
    }

    return std::make_unique<ForNode>(
        std::move(init),
        std::move(condition),
        std::move(increment),
        std::move(body),
        startLine,
        startColumn
    );
}

std::unique_ptr<IfNode> Parser::parseIfStatement()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();
    expect(TokenType::Keyword, "if");
    expect(TokenType::OpenParen);
    auto condition = parseExpression();
    expect(TokenType::CloseParen);

    std::unique_ptr<BlockNode> thenBlock = nullptr;
    std::vector<IfNode::ElseIfNode> elseIfBlocks;
    std::unique_ptr<BlockNode> elseBlock = nullptr;

    if (currentToken.getType() == TokenType::OpenBracket)
    {
        thenBlock = parseBlock();
    }
    // Handles single statement if blocks such as "if (true) return 0;"
    else
    {
        std::vector<std::unique_ptr<StatementNode>> singleStatement;
        singleStatement.push_back(parseStatement());
        thenBlock = std::make_unique<BlockNode>(std::move(singleStatement));
    }

    while (currentToken.getType() == TokenType::Keyword && currentToken.getValue() == "else")
    {
        advance();
        if (currentToken.getType() == TokenType::Keyword && currentToken.getValue() == "if")
        {
            advance();
            expect(TokenType::OpenParen);
            auto elseIfCondition = parseExpression();
            expect(TokenType::CloseParen);

            std::unique_ptr<BlockNode> elseIfBlock = nullptr;

            if (currentToken.getType() == TokenType::OpenBracket)
            {
                elseIfBlock = parseBlock();
            }
            else
            {
                std::vector<std::unique_ptr<StatementNode>> singleStatement;
                singleStatement.push_back(parseStatement());
                elseIfBlock = std::make_unique<BlockNode>(std::move(singleStatement));
            }
            elseIfBlocks.push_back(std::make_pair(std::move(elseIfCondition), std::move(elseIfBlock)));
        }
        else 
        {
            if (currentToken.getType() == TokenType::OpenBracket)
            {
                elseBlock = parseBlock();
            }
            else 
            {
                std::vector<std::unique_ptr<StatementNode>> singleStatement;
                singleStatement.push_back(parseStatement());
                elseBlock = std::make_unique<BlockNode>(std::move(singleStatement));
            }
        }
    }

    return std::make_unique<IfNode>(
        std::move(condition),
        std::move(thenBlock),
        std::move(elseIfBlocks),
        std::move(elseBlock)
    );
}

std::unique_ptr<WhileNode> Parser::parseWhileStatement()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    expect(TokenType::Keyword, "while");
    expect(TokenType::OpenParen);
    auto condition = parseExpression();
    expect(TokenType::CloseParen);

    std::unique_ptr<BlockNode> body = nullptr;
    if (currentToken.getType() == TokenType::OpenBracket)
    {
        body = parseBlock();
    }
    else 
    {
        std::vector<std::unique_ptr<StatementNode>> singleStatement;
        singleStatement.push_back(parseStatement());
        body = std::make_unique<BlockNode>(std::move(singleStatement));
    }

    return std::make_unique<WhileNode>(
        std::move(condition),
        std::move(body),
        startLine,
        startColumn
    );
}