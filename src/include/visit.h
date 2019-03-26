#ifndef TSCC_VISIT_H
#define TSCC_VISIT_H
#include "AST.h"
#include "ASTCompound.h"
#include "ASTBinop.h"
#include "ASTInteger.h"
#include "ASTDatatype.h"
#include "ASTFunctionDefinition.h"
//#include "ASTVariableDefinition.h"
void visit(AST* node);

void visit_ast_binop(AST_binop* node);

void visit_ast_integer(AST_integer* node);

void visit_ast_compound(AST_compound* node);

void visit_ast_datatype(AST_datatype* node);

void visit_ast_function_definition(AST_function_definition* node);

//void visit_ast_variable_definition(AST_variable_definition* node);
#endif
