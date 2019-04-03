#include "include/ASTFloat.h"
#include <stdlib.h>


AST_float* init_ast_float(token* t) {
    AST_float* _float = calloc(1, sizeof(struct AST_FLOAT_STRUCT));
    AST_constructor((AST*) _float, t, AST_FLOAT);

    return _float;
}
