#include "include/ASTFunctionDefinition.h"



AST_function_definition* init_ast_function_definition(token* t, char* name, dynamic_list* args, AST_compound* compound, AST_datatype* datatype) {
    AST_function_definition* fd = calloc(1, sizeof(struct AST_FUNCTION_DEFINITION_STRUCT));
    AST_constructor((AST*) fd, t, AST_FUNCTION_DEFINITION);

    
    fd->name = name;
    fd->args = args;
    fd->compound = compound;
    fd->datatype = datatype;
    
    return fd;
}
