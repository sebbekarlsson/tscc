#ifndef TSCC_AST_WHILE_H
#define TSCC_AST_WHILE_H
#include "AST.h"
#include "ASTCompound.h"

typedef struct AST_WHILE_STRUCT {
    AST base;
    AST* expr;
    AST_compound* compound;
} AST_while;

AST_while* init_ast_while(token* t, AST* expr, AST_compound* compound);
#endif
