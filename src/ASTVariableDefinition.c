#include "include/ASTVariableDefinition.h"
#include <stdlib.h>


AST_variable_definition* init_ast_variable_definition(token* t, char* name, AST* value, AST_datatype* datatype) {
    AST_variable_definition* vd = calloc(1, sizeof(struct AST_VARIABLE_DEFINITION_STRUCT));
    AST_constructor((AST*) vd, t, AST_VARIABLE_DEFINITION);

    vd->name = name;
    vd->value = value;
    vd->datatype = datatype;

    return vd;
}
