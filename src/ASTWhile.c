#include "include/ASTWhile.h"


AST_while* init_ast_while(token* t, AST* expr, AST_compound* compound) {
    AST_while* w = calloc(1, sizeof(struct AST_WHILE_STRUCT));
    AST_constructor((AST*) w, t, AST_WHILE);

    w->expr = expr;
    w->compound = compound;

    return w;
}
