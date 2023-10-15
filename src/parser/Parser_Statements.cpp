#include "parser/Parser.hpp"

std::unique_ptr<StatementNode> Parser::parseStatement()
{
    switch (currentToken.getType())
    {
        case TokenType::Identifier:
        {
            if (peekToken().getType() == TokenType::OpenParen)
            {
                return parseFunctionCallStatement();
            }
            else if (peekToken().getType() == TokenType::Assignment)
            {
                return parseAssignmentStatement();
            }
            else if (peekToken().getType() == TokenType::Increment || peekToken().getType() == TokenType::Decrement)
            {
                auto identifier = parseVariableReference();
                UnaryOperatorType op = tokenToUnaryOperatorType(currentToken);
                advance();
                expect(TokenType::Semicolon);
                return std::make_unique<UnaryExpressionNode>(std::move(identifier), op);
            }
            else
            {
                throw ParserException("Current token is indentifier, but expected function call, assignment, or unary expression", 
                    TokenType::OpenParen, peekToken());
            }
        }

        case TokenType::Keyword:
        {
            if (currentToken.getValue() == "for")
                return parseForStatement();
            else if (currentToken.getValue() == "if")
                return parseIfStatement();
            else if (currentToken.getValue() == "while")
                return parseWhileStatement();

            break;
        }
        
        case TokenType::Return:
        {
            return parseReturn();
        }
        
        // Pointer handling (ignore asterisks)
        case TokenType::Type:
        {
            int peekOffset = 1;

            while(peekToken(peekOffset).getType() == TokenType::Asterisk)
            {
                peekOffset++;
            }

            if (peekToken(peekOffset).getType() != TokenType::Identifier)
            {
                throw ParserException("Expected identifier after type in variable declaration/definition", 
                    TokenType::Identifier, peekToken(peekOffset));
            }

            peekOffset++;

            // Account for arrays
            while (peekToken(peekOffset).getType() == TokenType::OpenSquare)
            {
                // Increment the offset to skip over the contents of the array specifier
                do 
                {
                    peekOffset++;
                } 
                while (peekToken(peekOffset).getType() != TokenType::CloseSquare);

                peekOffset++;
            }

            if (peekToken(peekOffset).getType() == TokenType::Semicolon)
            {
                return parseVariableDeclaration();
            }
            else if (peekToken(peekOffset).getType() == TokenType::Assignment)
            {
                return parseVariableDefinition();
            }
            else
            {
                throw ParserException("Expected ';' or '=' after variable identifier", 
                    TokenType::Semicolon, peekToken(peekOffset));  
            }
        }

        case TokenType::Asterisk:
        {
            return handleAsteriskToken();
        }

        case TokenType::Minus:
        case TokenType::Exclamation:
        case TokenType::Increment:
        case TokenType::Decrement:
        case TokenType::Ampersand:
        {
            auto unaryExpression = parseUnaryExpression();
            expect(TokenType::Semicolon);
            return unaryExpression;
        }
        
        default:
            return nullptr;
    }
}

std::unique_ptr<ArraySpecifierNode> Parser::parseArraySpecifier()
{
    expect(TokenType::OpenSquare);
    std::unique_ptr<ExpressionNode> sizeNode = nullptr;

    // TODO: In this parser, arrays can only be declared with a size
    // So - include error handling in this if statement
    if (currentToken.getType() != TokenType::CloseSquare)
    {
        sizeNode = parseExpression();
    }

    expect(TokenType::CloseSquare);
    
    return std::make_unique<ArraySpecifierNode>(std::move(sizeNode));
}

std::unique_ptr<VariableDeclarationNode> Parser::parseVariableDeclaration()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    auto typeNode = parseType();
    auto identifierNode = parseIdentifier();

    std::vector<std::unique_ptr<ArraySpecifierNode>> arraySpecifiers;
    while (currentToken.getType() == TokenType::OpenSquare)
    {
        arraySpecifiers.push_back(parseArraySpecifier());
    }

    expect(TokenType::Semicolon);

    return std::make_unique<VariableDeclarationNode>(
        std::move(typeNode),
        std::move(identifierNode),
        std::move(arraySpecifiers),
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

    std::vector<std::unique_ptr<ArraySpecifierNode>> arraySpecifiers;
    while (currentToken.getType() == TokenType::OpenSquare)
    {
        arraySpecifiers.push_back(parseArraySpecifier());
    }

    expect(TokenType::Assignment);
    
    std::unique_ptr<Node> initializer;  // This can be an ArrayInitializerNode or an ExpressionNode
    if (currentToken.getType() == TokenType::OpenBracket)
    {
        initializer = parseArrayInitializer();
    }
    else
    {
        initializer = parseExpression();
    }
    
    expect(TokenType::Semicolon);

    return std::make_unique<VariableDefinitionNode>(
        std::move(typeNode),
        std::move(identifierNode),
        std::move(initializer),
        std::move(arraySpecifiers),
        startLine,
        startColumn
    );
}

std::unique_ptr<AssignmentStatementNode> Parser::parseAssignmentStatement()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    auto varRef = parseVariableReference();
    expect(TokenType::Assignment);
    auto value = parseExpression();
    expect(TokenType::Semicolon);

    return std::make_unique<AssignmentStatementNode>(
        std::move(varRef),
        std::move(value),
        startLine,
        startColumn
    );
}

std::unique_ptr<StatementNode> Parser::handleAsteriskToken()
{
    int peekOffset = 1;
    while (peekToken(peekOffset).getType() == TokenType::Asterisk)
    {
        peekOffset++;
    }

    if (peekToken(peekOffset).getType() == TokenType::Identifier 
        && peekToken(peekOffset + 1).getType() == TokenType::Assignment)
    {
        return parseDereferenceAssignment();
    }
    else
    {
        auto unaryExpression = parseUnaryExpression();
        expect(TokenType::Semicolon);
        return unaryExpression;
    }
}

std::unique_ptr<AssignmentStatementNode> Parser::parseDereferenceAssignment()
{
    int dereferenceCount = 0;
    while (currentToken.getType() == TokenType::Asterisk)
    {
        dereferenceCount++;
        advance();
    }

    auto varRef = parseVariableReference();
    expect(TokenType::Assignment);
    auto value = parseExpression();
    expect(TokenType::Semicolon);

    auto assignmentNode = std::make_unique<AssignmentStatementNode>(
        std::move(varRef),
        std::move(value),
        dereferenceCount,
        currentToken.getLine(),
        currentToken.getColumn()
    );

    return assignmentNode;
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