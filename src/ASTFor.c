#include "include/ASTFor.h"


AST_for* init_ast_for(token* t, dynamic_list* expressions, AST_compound* compound) {
    AST_for* f = calloc(1, sizeof(struct AST_FOR_STRUCT));
    AST_constructor((AST*) f, t, AST_FOR);

    f->expressions = expressions;
    f->compound = compound;

    return f;
}
