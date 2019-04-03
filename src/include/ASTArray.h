#ifndef TSCC_AST_ARRAY_H
#define TSCC_AST_ARRAY_H
#include "AST.h"
#include "ASTDatatype.h"
#include "dynamic_list.h"

typedef struct AST_ARRAY_STRUCT {
    AST base;
    AST_datatype* datatype;
    dynamic_list* elements;
} AST_array;

AST_array* init_ast_array(token* t, AST_datatype* datatype, dynamic_list* elements);
#endif
