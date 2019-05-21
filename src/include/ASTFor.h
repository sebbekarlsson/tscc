#ifndef TSCC_AST_FOR_H
#define TSCC_AST_FOR_H
#include "AST.h"
#include "ASTCompound.h"
#include "dynamic_list.h"

typedef struct AST_FOR_STRUCT {
    AST base;
    AST* expr;
    dynamic_list* expressions;
    AST_compound* compound;
} AST_for;

AST_for* init_ast_for(token* t, dynamic_list* expressions, AST_compound* compound);
#endif
