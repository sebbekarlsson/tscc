#include "include/visit.h"
#include <stdio.h>


void visit(AST* node) {
    if (!node)
        return;

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
        case AST_DATATYPE:
            return visit_ast_datatype((AST_datatype*) node);
        break;
        case AST_FUNCTION_DEFINITION:
            return visit_ast_function_definition((AST_function_definition*) node);
        break;
        //case VARIABLE_DEFINITION:
        //    return visit_ast_variable_definition((AST_variable_definition*) node);
        //break;
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

void visit_ast_datatype(AST_datatype* node) {
    printf(((AST*)node)->token->value);
}

void visit_ast_function_definition(AST_function_definition* node) {
    visit((AST*)node->datatype);
    printf(" ");
    printf(node->name);
    printf("(");

    for (int i = 0; i < node->args->size; i++) {
        visit((AST*) node->args->items[i]);
    }

    printf(")");
    printf("{\n");
    visit((AST*)node->compound);
    printf("\n}");
}

/*void visit_ast_variable_definition(AST_variable_definition* node) {

}*/
