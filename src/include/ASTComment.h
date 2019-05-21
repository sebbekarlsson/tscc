#ifndef TSCC_AST_COMMENT_H
#define TSCC_AST_COMMENT_H
#include "AST.h"

typedef struct AST_COMMENT_STRUCT {
    AST base;
} AST_comment;

AST_comment* init_ast_comment(token* t);
#endif
