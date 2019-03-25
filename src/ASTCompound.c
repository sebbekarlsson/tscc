#include "include/ASTCompound.h"
#include <stdlib.h>


AST_compound* init_ast_compound(token* t, dynamic_list* children) {
    AST_compound* compound = calloc(1, sizeof(struct AST_COMPOUND_STRUCT));
    compound->children = children; 
    AST_constructor((AST*) compound, t);

    return compound;
}
