#include "include/ASTClass.h"
#include <stdlib.h>


AST_class* init_ast_class(token* t, char* name, dynamic_list* variable_definitions, dynamic_list* function_definitions) {
    AST_class* c = calloc(1, sizeof(struct AST_CLASS_STRUCT));
    AST_constructor((AST*) c, t, AST_CLASS);

    c->name = name;
    c->variable_definitions = variable_definitions;
    c->function_definitions = function_definitions;

    c->constructor_function_definition = (void*) 0;

    return c;
}
