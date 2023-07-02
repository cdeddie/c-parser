#pragma once

#include "parser/AST/statement/declaration/DeclarationNode.hpp"
#include "parser/AST/expression/ExpressionNode.hpp"

class VariableDeclarationNode : public DeclarationNode
{
public:
	VariableDeclarationNode(
		std::unique_ptr<TypeNode> type, 
		std::unique_ptr<IdentifierNode> identifier, 
		std::unique_ptr<ExpressionNode> expression
	);

	const ExpressionNode& getInit() const;

    virtual void accept(const Visitor& visitor) const override;
private:
	std::unique_ptr<ExpressionNode> init;
};