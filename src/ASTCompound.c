#include "include/ASTCompound.h"
#include <stdlib.h>


AST_compound* init_ast_compound(token* t, dynamic_list* children) {
    AST_compound* a = calloc(1, sizeof(struct AST_COMPOUND_STRUCT));
    a->children = children; 
    AST_constructor((AST*) a, t);

    return a;
}
