#include "include/ASTIf.h"


AST_if* init_ast_if(token* t, AST* expr, AST_compound* compound, AST_if* otherwise) {
    AST_if* i = calloc(1, sizeof(struct AST_IF_STRUCT));
    AST_constructor((AST*) i, t, AST_IF);

    i->expr = expr;
    i->compound = compound;
    i->otherwise = otherwise;

    return i;
}
