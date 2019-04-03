#ifndef TSCC_AST_FLOAT_H
#define TSCC_AST_FLOAT_H
#include "AST.h"

typedef struct AST_FLOAT_STRUCT {
    AST base;
} AST_float;

AST_float* init_ast_float(token* t);
#endif
