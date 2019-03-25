#ifndef TSCC_AST_BINOP_H
#define TSCC_AST_BINOP_H
#include "AST.h"
#include "dynamic_list.h"

typedef struct AST_BINOP_STRUCT {
    AST base;
    AST* left;
    AST* right;
} AST_binop;

AST_binop* init_ast_binop(token* t, AST* left, AST* right);
#endif
