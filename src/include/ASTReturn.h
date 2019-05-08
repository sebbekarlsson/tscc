#ifndef TSCC_AST_RETURN_H
#define TSCC_AST_RETURN_H
#include "AST.h"
#include "dynamic_list.h"

typedef struct AST_RETURN_STRUCT {
	AST base;
	AST* statement;
} AST_return;

AST_return* init_ast_return(token* t, AST* statement);
#endif
