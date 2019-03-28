#include "include/ASTNull.h"
#include <stdlib.h>


AST_null* init_ast_null(token* t) {
    AST_null* null = calloc(1, sizeof(struct AST_NULL_STRUCT));
    AST_constructor((AST*) null, t, AST_NULL);

    return null;
}
