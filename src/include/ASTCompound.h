#ifndef TSCC_AST_COMPOUND_H
#define TSCC_AST_COMPOUND_H
#include "AST.h"
#include "dynamic_list.h"

typedef struct AST_COMPOUND_STRUCT {
    AST base;
    dynamic_list* children;
} AST_compound;

AST_compound* init_ast_compound(token* t, dynamic_list* children);
#endif
