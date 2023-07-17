#pragma once

#include "parser/AST/statement/FunctionDefinitionNode.hpp"
#include "parser/AST/ProgramNode.hpp"

#include "parser/AST/statement/FunctionDeclarationNode.hpp"
#include "parser/AST/statement/VariableDeclarationNode.hpp"
#include "parser/AST/statement/VariableDefinitionNode.hpp"
#include "parser/AST/statement/ReturnNode.hpp"
#include "parser/AST/statement/FunctionCallStatementNode.hpp"
#include "parser/AST/statement/ForNode.hpp"
#include "parser/AST/statement/IfNode.hpp"

#include "parser/AST/expression/ExpressionNode.hpp"
#include "parser/AST/expression/FunctionCallExpressionNode.hpp"
#include "parser/AST/expression/UnaryExpressionNode.hpp"
#include "parser/AST/expression/BinaryExpressionNode.hpp"
#include "parser/AST/expression/VariableReferenceNode.hpp"

#include "parser/AST/expression/literal/LiteralNode.hpp"
#include "parser/AST/expression/literal/IntegerLiteralNode.hpp"
#include "parser/AST/expression/literal/FloatLiteralNode.hpp"
#include "parser/AST/expression/literal/StringLiteralNode.hpp"
#include "parser/AST/expression/literal/CharLiteralNode.hpp"
