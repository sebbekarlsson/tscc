#include "include/ASTCompound.h"
#include <stdlib.h>


AST_compound* init_ast_compound(token* t, dynamic_list* children) {
    AST_compound* compound = calloc(1, sizeof(struct AST_COMPOUND_STRUCT));
    AST_constructor((AST*) compound, t, AST_COMPOUND);
   
    compound->children = children; 

    return compound;
}
