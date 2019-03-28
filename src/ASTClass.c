#include "include/ASTClass.h"
#include <stdlib.h>


AST_class* init_ast_class(token* t, char* name) {
    AST_class* c = calloc(1, sizeof(struct AST_CLASS_STRUCT));
    AST_constructor((AST*) c, t, AST_CLASS);

    c->name = name;

    return c;
}
