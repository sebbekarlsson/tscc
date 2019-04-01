#ifndef TSCC_AST_ASSIGNMENT_H
#define TSCC_AST_ASSIGNMENT_H
#include "AST.h"
#include "dynamic_list.h"

typedef struct AST_ASSIGNMENT_STRUCT {
    AST base;
    AST* left;
    AST* right;
} AST_assignment;

AST_assignment* init_ast_assignment(token* t, AST* left, AST* right);
#endif
