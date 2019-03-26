#include "include/ASTDatatype.h"
#include <stdlib.h>


AST_datatype* init_ast_datatype(token* t, int is_list) {
    AST_datatype* datatype = calloc(1, sizeof(struct AST_DATATYPE_STRUCT));
    AST_constructor((AST*) datatype, t, AST_DATATYPE);

    datatype->is_list = is_list;

    return datatype;
}
