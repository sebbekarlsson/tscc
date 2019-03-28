#include "include/visit.h"
#include "include/remap.h"
#include "include/strutils.h"
#include <stdio.h>
#include <string.h>


const char* CLASS_TEMPLATE = 
"typedef struct STRUCT_@CLASS_NAME{\n"
"}@CLASS_NAME;"
"\n"
"\n"
"@CLASS_NAME* init_@CLASS_NAME() {\n"
"    @CLASS_NAME* self = calloc(1, sizeof(struct STRUCT_@CLASS_NAME));\n"
"    return self;\n"
"}";

/**
 * Main entry point for visiting
 *
 * @param AST* node
 */
void visit(AST* node, outputbuffer* opb) {
    if (!node)
        return;

    switch (node->type) {
        case AST_COMPOUND:
            return visit_ast_compound((AST_compound*) node, opb);
        break;
        case AST_BINOP:
            return visit_ast_binop((AST_binop*) node, opb);
        break;
        case AST_INTEGER:
            return visit_ast_integer((AST_integer*) node, opb);
        break;
        case AST_DATATYPE:
            return visit_ast_datatype((AST_datatype*) node, opb);
        break;
        case AST_FUNCTION_DEFINITION:
            return visit_ast_function_definition((AST_function_definition*) node, opb);
        break;
        case AST_VARIABLE_DEFINITION:
            return visit_ast_variable_definition((AST_variable_definition*) node, opb);
        break;
        case AST_FUNCTION_CALL:
            return visit_ast_function_call((AST_function_call*) node, opb);
        break;
        case AST_STRING:
            return visit_ast_string((AST_string*) node, opb);
        break;
        case AST_IF:
            return visit_ast_if((AST_if*) node, opb);
        break;
        case AST_NULL:
            return visit_ast_null((AST_null*) node, opb);
        break;
        case AST_CLASS:
            return visit_ast_class((AST_class*) node, opb);
        break;
    }
}

void visit_ast_binop(AST_binop* node, outputbuffer* opb) {
    buff(opb, "(");
    visit(node->left, opb);
    buff(opb, ((AST*)node)->token->value);
    visit(node->right, opb);
    buff(opb, ")");
}

void visit_ast_integer(AST_integer* node, outputbuffer* opb) {
    buff(opb, ((AST*)node)->token->value);
}

void visit_ast_string(AST_string* node, outputbuffer* opb) {
    buff(opb, "\"");
    buff(opb, ((AST*)node)->token->value);
    buff(opb, "\"");
}

void visit_ast_compound(AST_compound* node, outputbuffer* opb) {
    for (int i = 0; i < node->children->size; i++) {
        visit((AST*) node->children->items[i], opb); buff(opb, ";\n");
    }
}

void visit_ast_datatype(AST_datatype* node, outputbuffer* opb) {
    AST* a = (AST*) node;

    if (strcmp(a->token->value, "number") == 0)
        buff(opb, "int");
    else if (strcmp(a->token->value, "string") == 0)
        buff(opb, "char*");
    else if (strcmp(a->token->value, "null") == 0)
        buff(opb, "void*");
    else
        buff(opb, "void");

    if (node->is_list)
        buff(opb, "*");
}

void visit_ast_function_definition(AST_function_definition* node, outputbuffer* opb) {
    visit((AST*)node->datatype, opb);
    buff(opb, " ");
    buff(opb, node->name);
    buff(opb, "(");

    for (int i = 0; i < node->args->size; i++) {
        visit((AST*) node->args->items[i], opb);

        if (i < node->args->size - 1)
            buff(opb, ", ");
    }

    buff(opb, ")");
    buff(opb, "{\n");
    visit((AST*)node->compound, opb);
    buff(opb, "}");
}

void visit_ast_variable_definition(AST_variable_definition* node, outputbuffer* opb) {
    visit((AST*) node->datatype, opb);
    buff(opb, " ");
    buff(opb, node->name);
    
    if (node->value) {
        buff(opb, " = ");
        visit(node->value, opb);
    }
}

void visit_ast_function_call(AST_function_call* node, outputbuffer* opb) {
    buff(opb, remap_function(node->name, opb));
    buff(opb, "(");

    for (int i = 0; i < node->args->size; i++) {
        visit((AST*) node->args->items[i], opb);

        if (i < node->args->size - 1)
            buff(opb, ", ");
    }

    buff(opb, ")");
}

void visit_ast_if(AST_if* node, outputbuffer* opb) {
    if (node->expr) {
        buff(opb, "if");
        buff(opb, "(");
        visit(node->expr, opb);
        buff(opb, ")");
    }

    buff(opb, "{\n");
    visit((AST*) node->compound, opb);
    buff(opb, "}");
    
    if (node->otherwise) {
        buff(opb, "else ");
        visit(node->otherwise, opb);
    }
}

void visit_ast_null(AST_null* node, outputbuffer* opb) {
    buff(opb, "(void*) 0");
}

void visit_ast_class(AST_class* node, outputbuffer* opb) {
    outputbuffer_require(opb, "<stdlib.h>");

    char* buffer = calloc(strlen(CLASS_TEMPLATE), sizeof(char));
    strcpy(buffer, CLASS_TEMPLATE);

    buff(opb, str_replace(buffer, "@CLASS_NAME", node->name));

    free(buffer);
}
