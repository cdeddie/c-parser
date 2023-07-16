#include "parser/Parser.hpp"

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.nextToken())
{
    
}

Token Parser::peekToken(int n) const
{
    return lexer.peekToken(n);
}

Token Parser::peekToken() const
{
    return lexer.peekToken();
}

// print next n tokens. printTokens(0) prints current token only
void Parser::printTokens(int n)
{
    if (n < 1)
    {
        return;
    }
    for (int i = 0; i < n; i++)
    {
        Token token = peekToken(i);
        std::cout << "Token " << i + 1 << ": " << token.typeToString() << 
                    " | value: [ " << token.getValue() << " ]" <<
                    " (line " << token.getLine() << ", column " << token.getColumn() << ")\n";
    }
}

void Parser::advance()
{
    currentToken = lexer.nextToken();
}

// Optional string parameter, only used for Keywords and Types
// std::optional needs to be dereferenced to access the value it wraps
void Parser::expect(TokenType type, std::optional<std::string> value)
{
    if (currentToken.getType() == type && (!value || currentToken.getValue() == *value))
    {
        advance();
    }
    else
    {
        std::string errorMsg = "Unexpected token: " + currentToken.getValue() + 
            " at line " + std::to_string(currentToken.getLine()) + " column " + std::to_string(currentToken.getColumn())
            + ". Expected: " + Token::toString(type);
        throw std::runtime_error(errorMsg);
    }
}

std::unique_ptr<AST> Parser::parse()
{
    try
    {
        auto programNode = parseProgram();

        if (currentToken.getType() != TokenType::EndOfFile)
        {
            throw ParserException("Unexpected End of File", TokenType::EndOfFile, currentToken);
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
    
    std::cout << "Parsing...\n";

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
                int i = 3; // peekToken parameter
                while (peekToken(i).getType() != TokenType::CloseParen)
                {
                    i++;
                }

                if (peekToken(i+1).getType() == TokenType::OpenBracket)
                {
                    programNodes.push_back(parseFunctionDefinition());
                }
                else if (peekToken(i+1).getType() == TokenType::Semicolon)
                {
                    programNodes.push_back(parseFunctionDeclaration());
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
                // Debugging
                std::cout << "After logic\n";

                throw std::runtime_error("Invalid syntax at line " + std::to_string(lexer.getCurrentLine()) + ", column " + std::to_string(lexer.getCurrentColumn()));
            }
        }
        else 
        {
            throw ParserException("Expected a type declaration or definition in parseProgram()", TokenType::Type, currentToken);
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
        throw ParserException("Expected a type", TokenType::Type, currentToken);
    }
    auto typeNode = std::make_unique<TypeNode>(currentToken.getValue(), currentToken.getLine(), currentToken.getColumn());
    advance();
    return typeNode;
}

std::unique_ptr<IdentifierNode> Parser::parseIdentifier()
{
    if (currentToken.getType() != TokenType::Identifier)
    {
        throw ParserException("Expected an identifier", TokenType::Identifier, currentToken);
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
    

    if (peekToken().getType() == TokenType::CloseParen)
    {
        std::cout << "No parameters\n";
        advance();
        return parameters;
    }

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
            throw ParserException("Expected a comma or closing parentheses in parameter list", TokenType::Comma, currentToken);
        }
    }

    // Consumes closing paren
    advance();
    return parameters;
}

std::unique_ptr<BlockNode> Parser::parseBlock()
{
    std::cout << "Parsing block\n";
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    expect(TokenType::OpenBracket);

    std::vector<std::unique_ptr<StatementNode>> statements;

    while (currentToken.getType() != TokenType::CloseBracket)
    {
        auto statement = parseStatement();
        statements.push_back(std::move(statement));
    }
    std::cout << "Block successfully parsed\n";

    expect(TokenType::CloseBracket);

    return std::make_unique<BlockNode>(std::move(statements), startLine, startColumn);
}
