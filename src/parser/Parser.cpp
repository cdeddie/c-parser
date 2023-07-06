#include "parser/Parser.hpp"

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.nextToken())
{
    
}

Token Parser::peekToken(int n)
{
    return lexer.peekToken(n);
}

Token Parser::peekToken()
{
    return lexer.peekToken();
}

void Parser::advance()
{
    currentToken = lexer.nextToken();
}

// Optional string parameter, only used for Keywords and Types
// std::optional needs to be dereferenced to access the value it wraps
void Parser::expect(TokenType type, const std::optional<std::string>& value)
{
    if (currentToken.getType() == type && (!value || currentToken.getValue() == *value))
    {
        advance();
    }
    else
    {
        std::string errorMsg = "Unexpected token: " + currentToken.getValue() + 
            " at line " + std::to_string(currentToken.getLine()) + " column " + std::to_string(currentToken.getColumn())
            + ". Expected: " + TokenTypeToString(type);
        throw std::runtime_error(errorMsg);
    }
}

std::string Parser::TokenTypeToString(TokenType type) {
    auto it = tokenTypeStrings.find(type);
    if (it != tokenTypeStrings.end())
        return it->second;
    else
        throw std::runtime_error("Unknown TokenType");
}

std::unique_ptr<AST> Parser::parse()
{
    try
    {
        auto programNode = parseProgram();

        if (currentToken.getType() != TokenType::EndOfFile)
        {
            throw std::runtime_error("Expected end of file");
        }

        return std::make_unique<AST>(std::move(programNode));
    }
    catch(const std::exception& error)
    {
        std::cerr << "Error during parsing: " << error.what() << std::endl;
        return nullptr;
    }
    
}

std::unique_ptr<ProgramNode> Parser::parseProgram()
{
    std::vector<std::unique_ptr<StatementNode>> programNodes;

    while (currentToken.getType() != TokenType::EndOfFile)
    {
        if (lexer.isAtEnd())
        {
            throw std::runtime_error("Unexpected end of lexer input");
        }

        if (currentToken.getType() == TokenType::Type && peekToken().getType() == TokenType::Identifier)
        {
            // Functions
            if (peekToken(2).getType() == TokenType::OpenParen)
            {
                // Declaration
                if (peekToken(4).getType() == TokenType::Semicolon)
                {
                    programNodes.push_back(parseFunctionDeclaration());
                }
                // Definition
                else if (peekToken(4).getType() == TokenType::OpenBracket)
                {
                    programNodes.push_back(parseFunctionDefinition());
                }
            }
            // Variables
            else if (peekToken(2).getType() == TokenType::Semicolon || peekToken(2).getType() == TokenType::Assignment)
            {
                // Declaration
                if (peekToken(2).getType() == TokenType::Semicolon)
                {
                    programNodes.push_back(parseVariableDeclaration());
                }
                // Definition
                else if (peekToken(2).getType() == TokenType::Assignment)
                {
                    programNodes.push_back(parseVariableDefinition());
                }
            }
            // Errors
            else
            {
                throw std::runtime_error("Invalid syntax in source file");
            }
        }
        else 
        {
            throw std::runtime_error("Expected a type declaration or definition");
        }
    }

    return std::make_unique<ProgramNode>(std::move(programNodes), currentToken.getLine(), currentToken.getColumn());
}

std::unique_ptr<FunctionDefinitionNode> Parser::parseFunctionDefinition()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    auto typeNode = parseType();
    auto identifierNode = parseIdentifier();
    auto parameters = parseParameters();
    auto blockNode = parseBlock();

    auto functionDefinitionNode = std::make_unique<FunctionDefinitionNode>(
        std::move(typeNode), 
        std::move(identifierNode), 
        std::move(parameters), 
        std::move(blockNode),
        startLine,
        startColumn
    );

    advance();
    return functionDefinitionNode;
}

std::unique_ptr<FunctionDeclarationNode> Parser::parseFunctionDeclaration()
{
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    auto returnTypeNode = parseType();
    auto functionNameNode = parseIdentifier();
    auto parameters = parseParameters();

    auto functionDeclarationNode = std::make_unique<FunctionDeclarationNode>(
        std::move(returnTypeNode),
        std::move(functionNameNode),
        std::move(parameters),
        startLine,
        startColumn
    );

    advance();
    return functionDeclarationNode;
}

std::unique_ptr<TypeNode> Parser::parseType()
{
    if (currentToken.getType() != TokenType::Type)
    {
        throw std::runtime_error("Expected a type");
    }
    auto typeNode = std::make_unique<TypeNode>(currentToken.getValue(), currentToken.getLine(), currentToken.getColumn());
    advance();
    return typeNode;
}

std::unique_ptr<IdentifierNode> Parser::parseIdentifier()
{
    if (currentToken.getType() != TokenType::Identifier)
    {
        throw std::runtime_error("Expected an identifier ");
    }
    auto identifierNode = std::make_unique<IdentifierNode>(currentToken.getValue(), currentToken.getLine(), currentToken.getColumn());
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
        int startLine = currentToken.getLine();
        int startColumn = currentToken.getColumn();

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
        parameters.emplace_back(std::make_unique<ParameterNode>(
            std::move(typeNode), std::move(identifierNode), 
            startLine, startColumn)
        );

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
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    expect(TokenType::OpenBracket);

    std::vector<std::unique_ptr<StatementNode>> statements;

    while (currentToken.getType() != TokenType::CloseParen)
    {
        auto statement = parseStatement();
        statements.push_back(std::move(statement));
    }

    expect(TokenType::CloseBracket);

    return std::make_unique<BlockNode>(std::move(statements), startLine, startColumn);
}

// -------------------------- String to enum class mapping --------------------------

const std::map<TokenType, std::string> Parser::tokenTypeStrings = {
    { TokenType::Identifier, "Identifier" },
    { TokenType::Keyword, "Keyword" },
    { TokenType::Return, "Return" },
    { TokenType::Type, "Type" },
    { TokenType::Symbol, "Symbol" },
    { TokenType::Integer, "Integer" },
    { TokenType::Float, "Float" },
    { TokenType::StringLiteral, "StringLiteral" },
    { TokenType::CharLiteral, "CharLiteral" },
    { TokenType::Assignment, "Assignment" },
    { TokenType::Whitespace, "Whitespace" },
    { TokenType::Comment, "Comment" },
    { TokenType::EndOfFile, "EndOfFile" },
    { TokenType::Error, "Error" },
    { TokenType::Semicolon, "Semicolon" },
    { TokenType::OpenParen, "OpenParen" },
    { TokenType::CloseParen, "CloseParen" },
    { TokenType::OpenBracket, "OpenBracket" },
    { TokenType::CloseBracket, "CloseBracket" },
    { TokenType::Comma, "Comma" },
    { TokenType::Plus, "Plus" },
    { TokenType::Minus, "Minus" },
    { TokenType::Asterisk, "Asterisk" },
    { TokenType::Modulus, "Modulus" },
    { TokenType::ForwardSlash, "ForwardSlash" },
    { TokenType::Increment, "Increment" },
    { TokenType::Decrement, "Decrement" },
    { TokenType::Ampersand, "Ampersand" },
    { TokenType::Exclamation, "Exclamation" },
    { TokenType::Negation, "Negation" },
    { TokenType::And, "And" },
    { TokenType::Or, "Or" },
    { TokenType::Equals, "Equals" },
    { TokenType::NotEquals, "NotEquals" },
    { TokenType::LessThan, "LessThan" },
    { TokenType::GreaterThan, "GreaterThan" },
    { TokenType::LessThanOrEqual, "LessThanOrEqual" },
    { TokenType::GreaterThanOrEqual, "GreaterThanOrEqual" },
    { TokenType::PreprocessorDirective, "PreprocessorDirective" }
};
