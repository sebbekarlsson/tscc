#ifndef TSCC_AST_OBJECT_INIT_H
#define TSCC_AST_OBJECT_INIT_H
#include "AST.h"
#include "ASTFunctionCall.h"

typedef struct AST_OBJECT_INIT_STRUCT {
    AST base;
    AST_function_call* function_call;
} AST_object_init;

AST_object_init* init_ast_object_init(token* t, AST_function_call* fc);
#endif
