#ifndef TSCC_AST_H
#define TSCC_AST_H
#include "token.h"
typedef struct AST_STRUCT {
    token* token;
} AST;

void AST_constructor(AST* ast, token* t);
#endif
