#pragma once

#include "parser/AST/FunctionDefinitionNode.hpp"
#include "parser/AST/ProgramNode.hpp"

#include "parser/AST/statement/declaration/DeclarationNode.hpp"
#include "parser/AST/statement/declaration/FunctionDeclarationNode.hpp"
#include "parser/AST/statement/declaration/VariableDeclarationNode.hpp"

#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/expression/FunctionCallNode.hpp"
#include "parser/AST/expression/UnaryExpressionNode.hpp"
#include "parser/AST/expression/BinaryExpressionNode.hpp"
#include "parser/AST/expression/VariableReferenceNode.hpp"

#include "parser/AST/expression/literal/LiteralNode.hpp"
#include "parser/AST/expression/literal/IntegerLiteralNode.hpp"
#include "parser/AST/expression/literal/FloatLiteralNode.hpp"
#include "parser/AST/expression/literal/StringLiteralNode.hpp"
#include "parser/AST/expression/literal/CharLiteralNode.hpp"

#include "parser/AST/statement/ReturnNode.hpp"