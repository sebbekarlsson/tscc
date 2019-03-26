#ifndef TSCC_AST_STRING_H
#define TSCC_AST_STRING_H
#include "AST.h"
#include "dynamic_list.h"

typedef struct AST_STRING_STRUCT {
    AST base;
} AST_string;

AST_string* init_ast_string(token* t);
#endif
