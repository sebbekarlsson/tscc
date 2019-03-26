#include "include/visit.h"
#include <stdio.h>


void visit(AST* node) {
    switch (node->type) {
        case AST_COMPOUND:
            return visit_ast_compound((AST_compound*) node);
        break;
        case AST_BINOP:
            return visit_ast_binop((AST_binop*) node);
        break;
        case AST_INTEGER:
            return visit_ast_integer((AST_integer*) node);
        break;
    }
}

void visit_ast_binop(AST_binop* node) {
    printf("(");
    visit(node->left);
    printf(((AST*)node)->token->value);
    visit(node->right);
    printf(")");
}

void visit_ast_integer(AST_integer* node) {
    printf(((AST*)node)->token->value);
}

void visit_ast_compound(AST_compound* node) {
    for (int i = 0; i < node->children->size; i++)
        visit((AST*) node->children->items[i]);
}
