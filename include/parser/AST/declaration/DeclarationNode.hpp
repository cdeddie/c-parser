#pragma once

#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/TypeNode.hpp"
#include "parser/AST/IdentifierNode.hpp"
#include <string>

// DeclarationNode currently contains an ExpressionNode member
// May not be necessary, for example function declarations do not
// usually have expressions. Might change.
class DeclarationNode : public Node 
{
public:
	DeclarationNode(
		std::unique_ptr<TypeNode> type, 
		std::unique_ptr<IdentifierNode> identifier, 
		std::unique_ptr<ExpressionNode> expression
	);
	virtual ~DeclarationNode() = default; 

	const TypeNode& getType() const;
    const IdentifierNode& getIdentifier() const;
    const ExpressionNode& getExpression() const;

protected:
	std::unique_ptr<TypeNode> type;
	std::unique_ptr<IdentifierNode> identifier;
	std::unique_ptr<ExpressionNode> expression;
};
