#ifndef TSCC_AST_DATATYPE_H
#define TSCC_AST_DATATYPE_H
#include "AST.h"

typedef struct AST_DATATYPE_STRUCT {
    AST base;
} AST_datatype;

AST_datatype* init_ast_datatype(token* t);
#endif
