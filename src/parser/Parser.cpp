#include "parser/Parser.hpp"

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.nextToken())
{
	
}

Token Parser::peekToken()
{
    return lexer.peekToken();
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
        // add children
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
    std::vector<std::unique_ptr<ParameterNode>> parameters;

    // Example: (int x, int y)
    expect(TokenType::OpenParen);

    while (currentToken.getType() != TokenType::CloseParen)
    {
        auto typeNode = parseType();
        auto identifierNode = parseIdentifier();

        // void parameter in c, i.e. int main(void)
        if (currentToken.getType() == TokenType::Type && currentToken.getValue() == "void")
        {
            advance();
            expect(TokenType::CloseParen);
            return parameters;
        }

        // Emplace constructs the object
        parameters.emplace_back(std::make_unique<ParameterNode>(std::move(typeNode), std::move(identifierNode)));

        if (currentToken.getType()  == TokenType::Comma)
        {
            advance();
        }

        else if (currentToken.getType() != TokenType::CloseParen)
        {
            throw std::runtime_error("Expected a comma or closing parentheses in parameter list");
        }
    }

    // Consumes closing paren
    advance();
    return parameters;
}

std::unique_ptr<BlockNode> Parser::parseBlock()
{
    expect(TokenType::OpenBracket);

    auto blockNode = std::make_unique<BlockNode>();

    // Enter new scope
    env.pushScope();

    while (currentToken.getType() != TokenType::CloseParen)
    {
        auto statement = parseStatement();
        blockNode->addStatement(std::move(statement));
    }

    // Leave scope
    env.popScope();

    expect(TokenType::CloseBracket);

    return blockNode;
}

