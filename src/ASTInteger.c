#include "include/ASTInteger.h"


AST_integer* init_ast_integer(token* t) {
    AST_integer* integer = calloc(1, sizeof(struct AST_INTEGER_STRUCT));
    AST_constructor((AST*) integer, t);

    return integer;
}
