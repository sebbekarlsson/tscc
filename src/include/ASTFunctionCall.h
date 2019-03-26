#ifndef TSCC_AST_FUNCTION_CALL_H
#define TSCC_AST_FUNCTION_CALL_H
#include "AST.h"
#include "dynamic_list.h"
#include "ASTCompound.h"

typedef struct AST_FUNCTION_CALL_STRUCT {
    AST base;
    char* name;
    dynamic_list* args;
} AST_function_call;

AST_function_call* init_ast_function_call(token* t,char* name, dynamic_list* args);
#endif
