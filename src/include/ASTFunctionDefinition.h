#ifndef TSCC_AST_FUNCTION_DEFINITION_H
#define TSCC_AST_FUNCTION_DEFINITION_H
#include "AST.h"
#include "dynamic_list.h"
#include "ASTDatatype.h"
#include "ASTCompound.h"

typedef struct AST_FUNCTION_DEFINITION_STRUCT {
    AST base;
    char* name;
    dynamic_list* args;
    AST_compound* compound;
    AST_datatype* datatype;
} AST_function_definition;

AST_function_definition* init_ast_function_definition(token* t,char* name, dynamic_list* args, AST_compound* compound, AST_datatype* datatype);
#endif
