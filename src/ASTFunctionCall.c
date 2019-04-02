#include "include/ASTFunctionCall.h"


AST_function_call* init_ast_function_call(token* t, char* name, dynamic_list* args) {
    AST_function_call* fc = calloc(1, sizeof(struct AST_FUNCTION_CALL_STRUCT));
    AST_constructor((AST*) fc, t, AST_FUNCTION_CALL);

    fc->name = name;
    fc->args = args;
    fc->self = (void*) 0;

    return fc;
}
