#include "include/ASTObjectInit.h"


AST_object_init* init_ast_object_init(token* t, AST_function_call* fc) {
    AST_object_init* oi = calloc(1, sizeof(struct AST_OBJECT_INIT_STRUCT));
    AST_constructor((AST*) oi, t, AST_OBJECT_INIT);

    oi->function_call = fc;

    return oi;
}
