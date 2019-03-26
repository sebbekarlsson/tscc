#include "include/visit.h"
#include "include/remap.h"
#include <stdio.h>
#include <string.h>

/**
 * Main entry point for visiting
 *
 * @param AST* node
 */
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
        case AST_VARIABLE_DEFINITION:
            return visit_ast_variable_definition((AST_variable_definition*) node);
        break;
        case AST_FUNCTION_CALL:
            return visit_ast_function_call((AST_function_call*) node);
        break;
        case AST_STRING:
            return visit_ast_string((AST_string*) node);
        break;
        case AST_IF:
            return visit_ast_if((AST_if*) node);
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

void visit_ast_string(AST_string* node) {
    printf("\"");
    printf(((AST*)node)->token->value);
    printf("\"");
}

void visit_ast_compound(AST_compound* node) {
    for (int i = 0; i < node->children->size; i++) {
        visit((AST*) node->children->items[i]); printf(";");
    }
}

void visit_ast_datatype(AST_datatype* node) {
    AST* a = (AST*) node;

    if (strcmp(a->token->value, "number") == 0)
        printf("int");
    else if (strcmp(a->token->value, "string") == 0)
        printf("char*");
    else
        printf("void");

    if (node->is_list)
        printf("*");
}

void visit_ast_function_definition(AST_function_definition* node) {
    visit((AST*)node->datatype);
    printf(" ");
    printf(node->name);
    printf("(");

    for (int i = 0; i < node->args->size; i++) {
        visit((AST*) node->args->items[i]);

        if (i < node->args->size - 1)
            printf(", ");
    }

    printf(")");
    printf("{\n");
    visit((AST*)node->compound);
    printf("\n}");
}

void visit_ast_variable_definition(AST_variable_definition* node) {
    visit((AST*) node->datatype);
    printf(" ");
    printf(node->name);
    
    if (node->value) {
        printf(" = ");
        visit(node->value);
    }
}

void visit_ast_function_call(AST_function_call* node) {
    printf(remap_function(node->name));
    printf("(");

    for (int i = 0; i < node->args->size; i++) {
        visit((AST*) node->args->items[i]);

        if (i < node->args->size - 1)
            printf(", ");
    }

    printf(")");
}

void visit_ast_if(AST_if* node) {
    if (node->expr) {
        printf("if");
        printf("(");
        visit(node->expr);
        printf(")");
    }

    printf("{\n");
    visit((AST*) node->compound);
    printf("\n}");
    
    if (node->otherwise) {
        printf("else ");
        visit(node->otherwise);
    }
}
