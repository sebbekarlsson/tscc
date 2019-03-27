#ifndef TSCC_VISIT_H
#define TSCC_VISIT_H
#include "outputbuffer.h"
#include "AST.h"
#include "ASTCompound.h"
#include "ASTBinop.h"
#include "ASTInteger.h"
#include "ASTString.h"
#include "ASTDatatype.h"
#include "ASTFunctionDefinition.h"
#include "ASTVariableDefinition.h"
#include "ASTFunctionCall.h"
#include "ASTIf.h"

void visit(AST* node, outputbuffer* opb);

void visit_ast_binop(AST_binop* node, outputbuffer* opb);

void visit_ast_integer(AST_integer* node, outputbuffer* opb);

void visit_ast_string(AST_string* node, outputbuffer* opb);

void visit_ast_compound(AST_compound* node, outputbuffer* opb);

void visit_ast_datatype(AST_datatype* node, outputbuffer* opb);

void visit_ast_function_definition(AST_function_definition* node, outputbuffer* opb);

void visit_ast_variable_definition(AST_variable_definition* node, outputbuffer* opb);

void visit_ast_function_call(AST_function_call* node, outputbuffer* opb);

void visit_ast_if(AST_if* node, outputbuffer* opb);
#endif
