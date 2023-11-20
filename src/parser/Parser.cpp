#include "parser/Parser.hpp"

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.nextToken())
{
    
}

// peekToken(int n) starts at 0, so peekToken(0) returns currentToken
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

// Don't need a main function, this function immediately starts parsing statements
// rather than looking for functions or global variables
std::unique_ptr<AST> Parser::parseTest()
{
    try 
    {
        std::vector<std::unique_ptr<StatementNode>> statements;

        while (currentToken.getType() != TokenType::EndOfFile) 
        {
            statements.push_back(parseStatement());
        }

        if (currentToken.getType() != TokenType::EndOfFile) 
        {
            throw ParserException("Unexpected tokens after statements", TokenType::EndOfFile, currentToken);
        }

        return std::make_unique<AST>(std::make_unique<ProgramNode>(std::move(statements), currentToken.getLine(), currentToken.getColumn()));
    } 
    catch (const std::exception& error) 
    {
        std::cerr << "Error during test parsing: " << error.what() << std::endl;
        return nullptr;
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

        if (currentToken.getType() != TokenType::Type)
        {
            throw ParserException("Expected a type declaration or definition in parseProgram()", TokenType::Type, currentToken);
        }

        // Offset to determine where to start parsing again after finding an asterisk (pointer grammar)
        // Starts at 1 for peekToken(int n) - when using peekToken with peekOffset, it will (hopefully)
        // start at the identifier - e.g. int** func(), peekToken(peekOffset).value = func
        int peekOffset = 1; 
        while (peekToken(peekOffset).getType() == TokenType::Asterisk)
        {
            peekOffset++;
        }

        
        if (peekToken(peekOffset).getType() != TokenType::Identifier)
        {
            throw std::runtime_error("Expected an identifier after type at line " + 
                                     std::to_string(lexer.getCurrentLine()) + ", column " + 
                                     std::to_string(lexer.getCurrentColumn()));
        }

        // Function declarations and definitions
        if (peekToken(peekOffset + 1).getType() == TokenType::OpenParen)
        {
            // i functions as an offset variable for peekToken()
            // Adding 2 because
            int i = peekOffset + 2; 
            // Looking ahead for function parameters
            while (peekToken(i).getType() != TokenType::CloseParen && peekToken(i).getType() != TokenType::EndOfFile)
            {
                i++;
            }

            // Once we know how far to peek to look past parameters, determine if the grammar
            // is a function definition or declaration
            if (peekToken(i + 1).getType() == TokenType::OpenBracket)
            {
                programNodes.push_back(parseFunctionDefinition());
            }
            else if (peekToken(i + 1).getType() == TokenType::Semicolon)
            {
                programNodes.push_back(parseFunctionDeclaration());
            }
        }

        // Variables
        else if (peekToken(peekOffset + 1).getType() == TokenType::Semicolon)
        {
            programNodes.push_back(parseVariableDeclaration());
        }
        else if (peekToken(peekOffset + 1).getType() == TokenType::Assignment)
        {
            programNodes.push_back(parseVariableDefinition());
        }
        
        else
        {
            throw std::runtime_error("Invalid syntax at line " + std::to_string(lexer.getCurrentLine()) + 
                                     ", column " + std::to_string(lexer.getCurrentColumn()));
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

    std::string typeName = currentToken.getValue();
    int line = currentToken.getLine();
    int column = currentToken.getColumn();

    advance();

    int pointerLevel = 0;
    while (currentToken.getType() == TokenType::Asterisk)
    {
        pointerLevel++;
        advance();
    }

    return std::make_unique<TypeNode>(typeName, pointerLevel, line, column);
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

    // Special case: void parameter -> int main(void)
    if (currentToken.getType() == TokenType::Type && currentToken.getValue() == "void")
    {
        advance();
        if (currentToken.getType() != TokenType::CloseParen)
        {
            throw ParserException("Unexpected token after 'void' in parameter list", TokenType::CloseParen, currentToken);
        }

        // Consumes closing paren
        advance();
        return parameters; 
    }

    // No parameters case
    if (currentToken.getType() == TokenType::CloseParen)
    {
        advance();
        return parameters;
    }

    while (currentToken.getType() != TokenType::CloseParen)
    {
        int startLine = currentToken.getLine();
        int startColumn = currentToken.getColumn();

        auto typeNode = parseType();
        auto identifierNode = parseIdentifier();

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
    int startLine = currentToken.getLine();
    int startColumn = currentToken.getColumn();

    expect(TokenType::OpenBracket);

    std::vector<std::unique_ptr<StatementNode>> statements;

    while (currentToken.getType() != TokenType::CloseBracket)
    {
        auto statement = parseStatement();
        statements.push_back(std::move(statement));
    }

    expect(TokenType::CloseBracket);

    return std::make_unique<BlockNode>(std::move(statements), startLine, startColumn);
}
