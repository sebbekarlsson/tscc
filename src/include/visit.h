#ifndef TSCC_VISIT_H
#define TSCC_VISIT_H
#include "AST.h"
#include "ASTCompound.h"
#include "ASTBinop.h"
#include "ASTInteger.h"
void visit(AST* node);

void visit_ast_binop(AST_binop* node);

void visit_ast_integer(AST_integer* node);

void visit_ast_compound(AST_compound* node);
#endif
