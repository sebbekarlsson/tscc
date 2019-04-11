#ifndef TSCC_VISIT_H
#define TSCC_VISIT_H
#include "outputbuffer.h"
#include "AST.h"
#include "ASTCompound.h"
#include "ASTBinop.h"
#include "ASTInteger.h"
#include "ASTFloat.h"
#include "ASTString.h"
#include "ASTDatatype.h"
#include "ASTFunctionDefinition.h"
#include "ASTVariableDefinition.h"
#include "ASTFunctionCall.h"
#include "ASTIf.h"
#include "ASTReturn.h"
#include "ASTNull.h"
#include "ASTClass.h"
#include "ASTUndefined.h"
#include "ASTObjectInit.h"
#include "ASTAttributeAccess.h"
#include "ASTVariable.h"
#include "ASTAssignment.h"
#include "ASTWhile.h"
#include "ASTArray.h"

void visit(AST* node, outputbuffer* opb);

void visit_ast_binop(AST_binop* node, outputbuffer* opb);

void visit_ast_integer(AST_integer* node, outputbuffer* opb);

void visit_ast_float(AST_float* node, outputbuffer* opb);

void visit_ast_string(AST_string* node, outputbuffer* opb);

void visit_ast_compound(AST_compound* node, outputbuffer* opb);

void visit_ast_datatype(AST_datatype* node, outputbuffer* opb);

void visit_ast_function_definition(AST_function_definition* node, outputbuffer* opb);

void visit_ast_variable_definition(AST_variable_definition* node, outputbuffer* opb);

void visit_ast_function_call(AST_function_call* node, outputbuffer* opb);

void visit_ast_if(AST_if* node, outputbuffer* opb);

void visit_ast_return_statement(AST_return* node, outputbuffer* opb);

void visit_ast_null(AST_null* node, outputbuffer* opb);

void visit_ast_class(AST_class* node, outputbuffer* opb);

void visit_ast_undefined(AST_undefined* node, outputbuffer* opb);

void visit_ast_object_init(AST_object_init* node, outputbuffer* opb);

void visit_ast_attribute_access(AST_attribute_access* node, outputbuffer* opb);

void visit_ast_variable(AST_variable* node, outputbuffer* opb);

void visit_ast_assignment(AST_assignment* node, outputbuffer* opb);

void visit_ast_while(AST_while* node, outputbuffer* opb);

void visit_ast_array(AST_array* node, outputbuffer* opb);
#endif
