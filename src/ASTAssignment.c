#include "include/ASTAssignment.h"
#include <stdlib.h>


AST_assignment* init_ast_assignment(token* t, AST* left, AST* right) {
    AST_assignment* assignment = calloc(1, sizeof(struct AST_ASSIGNMENT_STRUCT));
    AST_constructor((AST*) assignment, t, AST_ASSIGNMENT);

    assignment->left = left;
    assignment->right = right;

    return assignment;
}