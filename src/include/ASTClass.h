#ifndef TSCC_AST_CLASS_H
#define TSCC_AST_CLASS_H
#include "AST.h"

typedef struct AST_CLASS_STRUCT {
    AST base;
    char* name;
} AST_class;

AST_class* init_ast_class(token* t, char* name);
#endif
