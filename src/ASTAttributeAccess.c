#include "include/ASTAttributeAccess.h"
#include <stdlib.h>


AST_attribute_access* init_ast_attribute_access(token* t, AST* left, AST* right) {
    AST_attribute_access* aa = calloc(1, sizeof(struct AST_ATTRIBUTE_ACCESS_STRUCT));
    AST_constructor((AST*) aa, t, AST_ATTRIBUTE_ACCESS);

    aa->left = left;
    aa->right = right;

    return aa;
}
