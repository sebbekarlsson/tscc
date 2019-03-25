#ifndef TSCC_VISIT_H
#define TSCC_VISIT_H
#include "AST.h"
AST* visit(AST* node);

AST* visit_ast_binop(AST* node);

AST* visit_ast_integer(AST* node);
#endif
