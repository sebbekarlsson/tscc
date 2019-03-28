#include "include/ASTUndefined.h"
#include <stdlib.h>


AST_undefined* init_ast_undefined(token* t) {
    AST_undefined* u = calloc(1, sizeof(struct AST_UNDEFINED_STRUCT));
    AST_constructor((AST*) u, t, AST_UNDEFINED);

    return u;
}
