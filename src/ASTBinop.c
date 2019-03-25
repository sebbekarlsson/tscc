#include "include/ASTBinop.h"
#include <stdlib.h>


AST_binop* init_ast_binop(token* t, AST* left, AST* right) {
    AST_binop* binop = calloc(1, sizeof(struct AST_BINOP_STRUCT));
    AST_constructor((AST*) binop, t);

    binop->left = left;
    binop->right = right;

    return binop;
}
