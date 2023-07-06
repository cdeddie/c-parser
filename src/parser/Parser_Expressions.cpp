#include "parser/Parser.hpp"

std::unique_ptr<ExpressionNode> Parser::parseExpression()
{
    switch (currentToken.getType())
    {
        // Case for function call or variable ref
        case TokenType::Identifier:
            if (peekToken().getType() == TokenType::OpenParen)
                return parseFunctionCall();
            else
                return parseVariableReference();

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
        case TokenType::Plus:
        case TokenType::Minus:
        case TokenType::Exclamation:
        case TokenType::Increment:
        case TokenType::Decrement:
        case TokenType::Ampersand:
        case TokenType::Asterisk:
            return parseUnaryExpression();

        
        default:
            throw std::runtime_error("Unexpected token in expression");

    }
}

// identifier(expression_list)
std::unique_ptr<FunctionCallNode> Parser::parseFunctionCall() 
{
    std::unique_ptr<IdentifierNode> identifier = parseIdentifier();
    expect(TokenType::OpenParen);
    std::vector<std::unique_ptr<ExpressionNode>> args;

    while(currentToken.getType() != TokenType::CloseParen)
    {
        args.emplace_back(parseExpression());
        if (currentToken.getType() == TokenType::Comma)
            advance();
    }

    expect(TokenType::CloseParen);
    return std::make_unique<FunctionCallNode>(std::move(identifier), std::move(args));
}

// Need to test this thoroughly NEEDS UPDATING FOR ENUM CLASS
std::unique_ptr<UnaryExpressionNode> Parser::parseUnaryExpression() 
{
    static const std::unordered_map<TokenType, std::string> unaryOpMap = 
    {
        {TokenType::Plus, "+"},
        {TokenType::Minus, "-"},
        {TokenType::Exclamation, "!"},
        {TokenType::Increment, "++"},
        {TokenType::Decrement, "--"},
        {TokenType::Ampersand, "&"},
        {TokenType::Asterisk, "*"}
    };

    TokenType opType = currentToken.getType();
    auto opIter = unaryOpMap.find(opType);
    if (opIter == unaryOpMap.end())
    {
        throw std::runtime_error("Unexpected token in unary expression");
    }

    advance();

    return nullptr;
}

// TODO: Requires precedence parsing
std::unique_ptr<BinaryExpressionNode> Parser::parseBinaryExpression()
{
    return nullptr;
}

std::unique_ptr<VariableReferenceNode> Parser::parseVariableReference()
{
    std::unique_ptr<IdentifierNode> var = parseIdentifier();
    return std::make_unique<VariableReferenceNode>(std::move(var));
}

// ---------- Literal parsing ---------- /

std::unique_ptr<LiteralNode> Parser::parseLiteral() 
{
    return nullptr;
}

std::unique_ptr<IntegerLiteralNode> Parser::parseIntegerLiteral() {
    return nullptr;
}

std::unique_ptr<FloatLiteralNode> Parser::parseFloatLiteral() {
    return nullptr;
}

std::unique_ptr<StringLiteralNode> Parser::parseStringLiteral() {
    return nullptr;
}

std::unique_ptr<CharLiteralNode> Parser::parseCharLiteral() {
    return nullptr;
}