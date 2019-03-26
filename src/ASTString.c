#include "include/ASTString.h"


AST_string* init_ast_string(token* t) {
    AST_string* s = calloc(1, sizeof(struct AST_STRING_STRUCT));
    AST_constructor((AST*) s, t, AST_STRING);

    return s;
}
