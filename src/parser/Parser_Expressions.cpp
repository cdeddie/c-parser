#include "parser/Parser.hpp"

std::unique_ptr<ExpressionNode> Parser::parseExpression()
{
    auto left = parsePrimaryExpression();

    // If the next token is a binary operator, parse a binary expression.
    if (isBinaryOperator(currentToken)) {
        left = parseBinaryExpression(0, std::move(left));
    }

    return left;
}

std::unique_ptr<ExpressionNode> Parser::parsePrimaryExpression()
{
    switch (currentToken.getType())
    {
        case TokenType::OpenParen:
        {
            advance();
            auto expr = parseExpression();
            expect(TokenType::CloseParen);
            return expr;
        }
        case TokenType::OpenBracket:
            return parseArrayInitializer();

        // function call or variable ref
        case TokenType::Identifier:
        {
            if (peekToken().getType() == TokenType::OpenParen)
                return parseFunctionCallExpression();
            else
            {
                auto identifier = parseVariableReference();

                // Check for postfix increment/decrement 
                if (currentToken.getType() == TokenType::Increment || currentToken.getType() == TokenType::Decrement)
                {
                    UnaryOperatorType op = tokenToUnaryOperatorType(currentToken);
                    advance();
                    return std::make_unique<UnaryExpressionNode>(std::move(identifier), op);
                }

                // It's not a unary expression, so return as a variable reference
                return identifier;
            }
        }

        // Literal values
        case TokenType::Integer:
            return parseIntegerLiteral();
        case TokenType::Float:
            return parseFloatLiteral();
        case TokenType::CharLiteral:
            return parseCharLiteral();
        case TokenType::StringLiteral:
            return parseStringLiteral();

        // Unary expression (+, -, ! etc)
        case TokenType::Minus:
        case TokenType::Exclamation:
        case TokenType::Increment:
        case TokenType::Decrement:
        case TokenType::Ampersand:
        case TokenType::Asterisk:
            std::cout << "Recognized unary expression\n";
            return parseUnaryExpression();

        default:
            throw std::runtime_error("Unexpected token in expression");
    }
}

// identifier(expression_list)
std::unique_ptr<FunctionCallExpressionNode> Parser::parseFunctionCallExpression() 
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();
    std::unique_ptr<IdentifierNode> identifier = parseIdentifier();
    expect(TokenType::OpenParen);
    std::vector<std::unique_ptr<ExpressionNode>> args;

    while(currentToken.getType() != TokenType::CloseParen)
    {
        args.push_back(parseExpression());
        if (currentToken.getType() == TokenType::Comma)
            advance();
    }

    expect(TokenType::CloseParen);
    return std::make_unique<FunctionCallExpressionNode>(std::move(identifier), std::move(args), startLine, startColumn);
}

// -------- UnaryOperator helpers -------- //

Parser::UnaryOperatorNodeType Parser::getUnaryOperatorNodeType(const Token& token)
{
    switch(token.getType())
    {
        case TokenType::Increment:
        case TokenType::Decrement:
        case TokenType::Exclamation:
        case TokenType::Minus:
        case TokenType::Ampersand:
        case TokenType::Asterisk:
            return UnaryOperatorNodeType::Prefix;
        case TokenType::Identifier:
            if (peekToken().getType() == TokenType::Increment || peekToken().getType() == TokenType::Decrement)
            {
                return UnaryOperatorNodeType::Postfix;
            }
        default:
            return UnaryOperatorNodeType::None;
                                         
    }
}

UnaryOperatorType Parser::tokenToUnaryOperatorType(const Token& token) {
    std::string tokenValue = token.getValue();

    if (tokenValue == "++")
        return UnaryOperatorType::Increment;
    else if (tokenValue == "--")
        return UnaryOperatorType::Decrement;
    else if (tokenValue == "!")
        return UnaryOperatorType::Not;
    else if (tokenValue == "-")
        return UnaryOperatorType::Negate;
    else if (tokenValue == "*")
        return UnaryOperatorType::Dereference;
    else if (tokenValue == "&")
        return UnaryOperatorType::AddressOf;
    else
        throw std::runtime_error("Unexpected token value for UnaryOperatorNode operator: " + tokenValue);

}

// Need to test this thoroughly NEEDS UPDATING FOR ENUM CLASS
std::unique_ptr<UnaryExpressionNode> Parser::parseUnaryExpression() 
{
    UnaryOperatorNodeType opType = getUnaryOperatorNodeType(currentToken);
    std::unique_ptr<ExpressionNode> expr;

    if (opType == UnaryOperatorNodeType::Prefix)
    {
        UnaryOperatorType op = tokenToUnaryOperatorType(currentToken);
        advance();
        expr = parseExpression();
        return std::make_unique<UnaryExpressionNode>(std::move(expr), op);
    }

    expr = parseExpression();
    
    if (opType == UnaryOperatorNodeType::Postfix)
    {
        UnaryOperatorType op = tokenToUnaryOperatorType(currentToken);
        advance();
        return std::make_unique<UnaryExpressionNode>(std::move(expr), op);
    }

    return nullptr;
}

// -------- BinaryOperator helpers -------- //
bool Parser::isBinaryOperator(const Token& token)
{
    switch(token.getType())
    {
        case TokenType::Plus:
        case TokenType::Minus:
        case TokenType::Asterisk:
        case TokenType::ForwardSlash:
        case TokenType::Modulus:
        case TokenType::And:
        case TokenType::Or:
        case TokenType::Equals:
        case TokenType::NotEquals:
        case TokenType::LessThan: 
        case TokenType::GreaterThan: 
        case TokenType::LessThanOrEqual: 
        case TokenType::GreaterThanOrEqual: 
            return true;
        default:
            return false;
    }
}

int Parser::getBinaryOperatorPrecendence(const Token& token)
{
    if (!isBinaryOperator(token))
        return -1;

    switch(token.getType())
    {
        case TokenType::Asterisk:
        case TokenType::ForwardSlash:
        case TokenType::Modulus:
            return 5;
        case TokenType::Plus:
        case TokenType::Minus:
            return 4;
        case TokenType::LessThan:
        case TokenType::GreaterThan:
        case TokenType::LessThanOrEqual:
        case TokenType::GreaterThanOrEqual:
            return 3;
        case TokenType::Equals:
        case TokenType::NotEquals:
            return 2;
        case TokenType::And:
            return 1;
        case TokenType::Or:
            return 0;
        default:
            return -1;
    }
}

BinaryOperatorType Parser::tokenToBinaryOperatorType(const Token& token)
{
    switch(token.getType())
    {
        case TokenType::Plus:
            return BinaryOperatorType::Plus;
        case TokenType::Minus:
            return BinaryOperatorType::Minus;
        case TokenType::Asterisk:
            return BinaryOperatorType::Multiply;
        case TokenType::ForwardSlash:
            return BinaryOperatorType::Divide;
        case TokenType::Modulus:
            return BinaryOperatorType::Modulus;
        case TokenType::And:
            return BinaryOperatorType::And;
        case TokenType::Or: 
            return BinaryOperatorType::Or;
        case TokenType::Equals: 
            return BinaryOperatorType::Equals;
        case TokenType::NotEquals:
            return BinaryOperatorType::NotEquals;
        case TokenType::LessThan:
            return BinaryOperatorType::LessThan;
        case TokenType::GreaterThan:
            return BinaryOperatorType::GreaterThan;
        case TokenType::LessThanOrEqual:
            return BinaryOperatorType::LessThanOrEqual;
        case TokenType::GreaterThanOrEqual:
            return BinaryOperatorType::GreaterThanOrEqual;
        default:
            throw std::runtime_error("Unexpected token type for binary operator");
    }
}

std::unique_ptr<ExpressionNode> Parser::parseBinaryExpression(int exprPrec, std::unique_ptr<ExpressionNode> left)
{
    while (true)
    {
        int tokPrec = getBinaryOperatorPrecendence(currentToken);

        // Base case
        if (tokPrec < exprPrec)
            return left;
        
        BinaryOperatorType binOp = tokenToBinaryOperatorType(currentToken);
        advance();

        auto right = parseExpression();

        int nextPrec = getBinaryOperatorPrecendence(currentToken);
        if (tokPrec < nextPrec)
            right = parseBinaryExpression(tokPrec + 1, std::move(right));
        
        left = std::make_unique<BinaryExpressionNode>(std::move(left), std::move(right), binOp);
    }
}

std::unique_ptr<VariableReferenceNode> Parser::parseVariableReference()
{
    std::unique_ptr<IdentifierNode> var = parseIdentifier();
    std::vector<std::unique_ptr<ExpressionNode>> indices;

    while (currentToken.getType() == TokenType::OpenSquare)
    {
        advance();
        indices.push_back(parseExpression());
        expect(TokenType::CloseSquare);
    }

    return std::make_unique<VariableReferenceNode>(std::move(var), std::move(indices));
}

std::unique_ptr<ArrayInitializerNode> Parser::parseArrayInitializer()
{
    expect(TokenType::OpenBracket);
    
    std::vector<std::unique_ptr<ExpressionNode>> elements;
    while (currentToken.getType() != TokenType::CloseBracket)
    {
        elements.push_back(parseExpression());
        if (currentToken.getType() == TokenType::Comma)
        {
            advance();
        }
        else if (currentToken.getType() != TokenType::CloseBracket)
        {
            throw ParserException("Expected ',' or '}' in array initializer", 
                                  TokenType::Comma, currentToken);
        }
    }

    expect(TokenType::CloseBracket);
    
    return std::make_unique<ArrayInitializerNode>(std::move(elements));
}

// ---------- Literal parsing ---------- /
std::unique_ptr<LiteralNode> Parser::parseLiteral() 
{
    switch (currentToken.getType())
    {
        case TokenType::Integer:
            return parseIntegerLiteral();
        case TokenType::Float:
            return parseFloatLiteral();
        case TokenType::CharLiteral:
            return parseCharLiteral();
        case TokenType::StringLiteral:
            return parseStringLiteral();
        default:
            throw std::runtime_error("Unexpected token in literal");
    }
}

std::unique_ptr<IntegerLiteralNode> Parser::parseIntegerLiteral() {
    int value = std::stoi(currentToken.getValue());
    advance();
    return std::make_unique<IntegerLiteralNode>(value);
}

std::unique_ptr<FloatLiteralNode> Parser::parseFloatLiteral() {
    float value = std::stof(currentToken.getValue());
    advance();
    return std::make_unique<FloatLiteralNode>(value);
}

std::unique_ptr<StringLiteralNode> Parser::parseStringLiteral() {
    std::string value = currentToken.getValue();
    advance();
    return std::make_unique<StringLiteralNode>(value);
}

std::unique_ptr<CharLiteralNode> Parser::parseCharLiteral() {
    char value = currentToken.getValue()[1];
    advance();
    return std::make_unique<CharLiteralNode>(value);
}