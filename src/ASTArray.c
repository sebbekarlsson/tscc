#include "include/ASTArray.h"
#include <stdlib.h>


AST_array* init_ast_array(token* t, AST_datatype* datatype, dynamic_list* elements) {
    AST_array* array = calloc(1, sizeof(struct AST_ARRAY_STRUCT));
    AST_constructor((AST*) array, t, AST_ARRAY);

    array->datatype = datatype;
    array->elements = elements;

    return array;
}
