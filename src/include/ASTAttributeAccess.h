#ifndef TSCC_AST_ATTRIBUTE_ACCESS_H
#define TSCC_AST_ATTRIBUTE_ACCESS_H
#include "AST.h"
#include "ASTFunctionCall.h"

typedef struct AST_ATTRIBUTE_ACCESS_STRUCT {
    AST base;
    AST* left;
    AST* right;
} AST_attribute_access;

AST_attribute_access* init_ast_attribute_access(token* t, AST* left, AST* right);
#endif
