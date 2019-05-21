#include "include/ASTComment.h"
#include <stdlib.h>
#include <string.h>


AST_comment* init_ast_comment(token* t) {
    AST_comment* s = calloc(1, sizeof(struct AST_COMMENT_STRUCT));
    AST_constructor((AST*) s, t, AST_COMMENT);

    return s;
}
