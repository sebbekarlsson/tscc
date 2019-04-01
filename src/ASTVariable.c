#include "include/ASTVariable.h"
#include <stdlib.h>


AST_variable* init_ast_variable(token* t) {
    AST_variable* variable = calloc(1, sizeof(struct AST_VARIABLE_STRUCT));
    AST_constructor((AST*) variable, t, AST_VARIABLE);

    return variable;
}
