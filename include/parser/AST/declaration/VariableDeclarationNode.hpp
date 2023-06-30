#pragma once

#include "parser/Node.hpp"
#include "parser/AST/declaration/DeclarationNode.hpp"
#include "parser/AST/expression/ExpressionNode.hpp"

class VariableDeclarationNode : public DeclarationNode
{
public:
	VariableDeclarationNode(
		std::unique_ptr<TypeNode> type, 
		std::unique_ptr<IdentifierNode> identifier, 
		std::unique_ptr<ExpressionNode> expression
	);

	std::unique_ptr<ExpressionNode>& getInit() { return init; }
private:
	std::unique_ptr<ExpressionNode> init;
};