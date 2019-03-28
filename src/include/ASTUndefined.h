#ifndef TSCC_AST_UNDEFINED_H
#define TSCC_AST_UNDEFINED_H
#include "AST.h"

typedef struct AST_UNDEFINED_STRUCT {
    AST base;
} AST_undefined;

AST_undefined* init_ast_undefined(token* t);
#endif
