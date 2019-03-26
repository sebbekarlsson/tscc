#ifndef TSCC_AST_IF_H
#define TSCC_AST_IF_H
#include "AST.h"
#include "ASTDatatype.h"
#include "ASTCompound.h"

typedef struct AST_IF_STRUCT {
    AST base;
    AST* expr;
    AST_compound* compound;
    void* otherwise;
} AST_if;

AST_if* init_ast_if(token* t, AST* expr, AST_compound* compound, AST_if* otherwise);
#endif
