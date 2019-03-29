#ifndef TSCC_SCOPE_H
#define TSCC_SCOPE_H
#include "AST.h"

typedef struct SCOPE_STRUCT {
    AST* owner;
} scope;

scope* init_scope(AST* owner);
#endif
