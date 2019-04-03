#include "include/visit.h"
#include "include/remap.h"
#include "include/strutils.h"
#include "include/scope.h"
#include <stdio.h>
#include <string.h>


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
        case AST_FLOAT:
            return visit_ast_float((AST_float*) node, opb);
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
        case AST_UNDEFINED:
            return visit_ast_undefined((AST_undefined*) node, opb);
        break;
        case AST_OBJECT_INIT:
            return visit_ast_object_init((AST_object_init*) node, opb);
        break;
        case AST_ATTRIBUTE_ACCESS:
            return visit_ast_attribute_access((AST_attribute_access*) node, opb);
        break;
        case AST_VARIABLE:
            return visit_ast_variable((AST_variable*) node, opb);
        break;
        case AST_ASSIGNMENT:
            return visit_ast_assignment((AST_assignment*) node, opb);
        break;
        case AST_WHILE:
            return visit_ast_while((AST_while*) node, opb);
        break;
    }
}

/**
 * Visitor for AST_binop node
 *
 * @param AST_binop* node
 * @param outputbuffer* opb
 */
void visit_ast_binop(AST_binop* node, outputbuffer* opb) {
    //buff(opb, "(");
    visit(node->left, opb);
    buff(opb, ((AST*)node)->token->value);
    visit(node->right, opb);
    //buff(opb, ")");
}

/**
 * Visitor for AST_integer node
 *
 * @param AST_integer* node
 * @param outputbuffer* opb
 */
void visit_ast_integer(AST_integer* node, outputbuffer* opb) {
    buff(opb, ((AST*)node)->token->value);
}

/**
 * Visitor for AST_float node
 *
 * @param AST_float* node
 * @param outputbuffer* opb
 */
void visit_ast_float(AST_float* node, outputbuffer* opb) {
    buff(opb, ((AST*)node)->token->value);
    buff(opb, "f");
}

/**
 * Visitor for AST_string node
 *
 * @param AST_string* node
 * @param outputbuffer* opb
 */
void visit_ast_string(AST_string* node, outputbuffer* opb) {
    buff(opb, "\"");
    buff(opb, ((AST*)node)->token->value);
    buff(opb, "\"");
}

/**
 * Visitor for AST_compound node
 *
 * @param AST_compound* node
 * @param outputbuffer* opb
 */
void visit_ast_compound(AST_compound* node, outputbuffer* opb) {
    for (int i = 0; i < node->children->size; i++) {
        visit((AST*) node->children->items[i], opb); buff(opb, ";\n");
    }
}

/**
 * Visitor for AST_datatype node
 *
 * @param AST_datatype* node
 * @param outputbuffer* opb
 */
void visit_ast_datatype(AST_datatype* node, outputbuffer* opb) {
    AST* a = (AST*) node;

    if (strcmp(a->token->value, "number") == 0)
        buff(opb, "int");
    else if (strcmp(a->token->value, "string") == 0)
        buff(opb, "char*");
    else if (strcmp(a->token->value, "null") == 0 || strcmp(a->token->value, "undefined") == 0)
        buff(opb, "void*");
    else
        buff(opb, "void");

    if (node->is_list)
        buff(opb, "*");
}

/**
 * Visitor for AST_function_definition node
 *
 * @param AST_function_definition* node
 * @param outputbuffer* opb
 */
void visit_ast_function_definition(AST_function_definition* node, outputbuffer* opb) {
    AST* a = (AST*) node;
    AST_class* owner_class = (void*) 0;
   
    if (a->s) {
        scope* s = (scope*) a->s;
        if (s->owner) {
            if (s->owner->type == AST_CLASS) {
                owner_class = (AST_class*) s->owner;
            }
        }
    }

    if (owner_class && strcmp(node->name, "constructor") == 0) {
       buff(opb, owner_class->name);
       buff(opb, "*"); 
    } else {
        if (node->datatype) {
            visit((AST*)node->datatype, opb);
        } else {
            buff(opb, "void");
        }
    }

    buff(opb, " ");
    buff(opb, node->name);

    if (owner_class)
        buff(opb, owner_class->name);

    buff(opb, "(");

    if (owner_class && strcmp(node->name, "constructor") != 0) {
        buff(opb, owner_class->name);
        buff(opb, "* self");

        if (node->args->size >= 1)
            buff(opb, ", ");
    }

    for (int i = 0; i < node->args->size; i++) {
        visit((AST*) node->args->items[i], opb);

        if (i < node->args->size - 1)
            buff(opb, ", ");
    }

    buff(opb, ")");
    buff(opb, "{\n");

    if (strcmp(node->name, "main") == 0)
        buff(opb, "bootstrap();\n\n");
    
    if (owner_class && strcmp(node->name, "constructor") == 0) {
        buff(opb, owner_class->name);
        buff(opb, "* self = init_");
        buff(opb, owner_class->name);
        buff(opb, "();\n");
    }

    visit((AST*)node->compound, opb);

    if (owner_class && strcmp(node->name, "constructor") == 0)
        buff(opb, "return self;\n");

    buff(opb, "}");
}

/**
 * Visitor for AST_variable_definition node
 *
 * @param AST_variable_definition* node
 * @param outputbuffer* opb
 */
void visit_ast_variable_definition(AST_variable_definition* node, outputbuffer* opb) {
    if (node->value) {
        if (node->value->type == AST_OBJECT_INIT) {
            AST_object_init* oi = (AST_object_init*) node->value;
            buff(opb, oi->function_call->name);
            buff(opb, "*");
        } else {
            visit((AST*) node->datatype, opb);
        }
    } else {
        visit((AST*) node->datatype, opb);
    }
    buff(opb, " ");
    visit(node->left, opb);
    
    if (node->value) {
        if (node->value->type == AST_UNDEFINED)
            return;

        buff(opb, " = ");
        visit(node->value, opb);
    }
}

/**
 * Visitor for AST_function_call node
 *
 * @param AST_function_call* node
 * @param outputbuffer* opb
 */
void visit_ast_function_call(AST_function_call* node, outputbuffer* opb) {
    buff(opb, remap_function(node->name, opb));
    buff(opb, "(");

    if (node->self) {
        visit(node->self, opb);

        if (node->args->size)
            buff(opb, ",");
    }

    for (int i = 0; i < node->args->size; i++) {
        visit((AST*) node->args->items[i], opb);

        if (i < node->args->size - 1)
            buff(opb, ", ");
    }

    buff(opb, ")");
}

/**
 * Visitor for AST_if node
 *
 * @param AST_if* node
 * @param outputbuffer* opb
 */
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

/**
 * Visitor for AST_null node
 *
 * @param AST_null* node
 * @param outputbuffer* opb
 */
void visit_ast_null(AST_null* node, outputbuffer* opb) {
    buff(opb, "(void*) 0");
}

/**
 * Visitor for AST_class node
 *
 * @param AST_class* node
 * @param outputbuffer* opb
 */
void visit_ast_class(AST_class* node, outputbuffer* opb) {
    outputbuffer_require(opb, "<stdlib.h>");

    buff(opb, "typedef struct STRUCT_");
    buff(opb, node->name);
    buff(opb, "{");
    
    for (int i = 0; i < node->variable_definitions->size; i++) {
        AST_variable_definition* vd = (AST_variable_definition*) node->variable_definitions->items[i];
        visit((AST*) vd, opb); buff(opb, ";");
    }

    for (int i = 0; i < node->function_definitions->size; i++) {
        AST_function_definition* fd = (AST_function_definition*) node->function_definitions->items[i];
        
        if (strcmp(fd->name, "constructor") == 0) {
            buff(opb, "struct STRUCT_");
           buff(opb, node->name);
        } else {
            visit((AST*)fd->datatype, opb);
        }
        buff(opb, "* (*");
        buff(opb, fd->name);
        buff(opb, ")(");

        buff(opb, "struct STRUCT_");
        buff(opb, node->name);
        buff(opb, "* self");

        if (fd->args->size)
            buff(opb, ", ");
        
        for (int j = 0; j < fd->args->size; j++) {
            visit((AST*)fd->args->items[i], opb);

            if (i < fd->args->size - 1)
                buff(opb, ", ");
        }

        buff(opb, ");\n");
    }

    buff(opb, "}");
    buff(opb, node->name);
    buff(opb, ";");
    buff(opb, "\n");
    buff(opb, node->name);
    buff(opb, "* init_");
    buff(opb, node->name);
    buff(opb, "();\n");
    buff(opb, "\n");
    
    for (int i = 0; i < node->function_definitions->size; i++) {
        AST_function_definition* fd = (AST_function_definition*) node->function_definitions->items[i];

        visit((AST*) fd, opb);
    }

    buff(opb, "\n");
    buff(opb, "\n");
    buff(opb, node->name);
    buff(opb, "* init_");
    buff(opb, node->name);
    buff(opb, "() {\n");
    buff(opb, node->name);
    buff(opb, "* self = calloc(1, sizeof(struct STRUCT_");
    buff(opb, node->name);
    buff(opb, "));\n");
    
    for (int i = 0; i < node->function_definitions->size; i++) {
        AST_function_definition* fd = (AST_function_definition*) node->function_definitions->items[i];
        buff(opb, "self->");
        buff(opb, fd->name);
        buff(opb, " = ");
        buff(opb, fd->name);
        buff(opb, node->name);
        buff(opb, ";");
    }

    buff(opb, "return self;\n");
    buff(opb, "}"); 
}

/**
 * Visitor for AST_undefined node
 *
 * @param AST_undefined* node
 * @param outputbuffer* opb
 */
void visit_ast_undefined(AST_undefined* node, outputbuffer* opb) {
    // silence
}

/**
 * Visitor for AST_object_init node
 *
 * @param AST_object_init* node
 * @param outputbuffer* opb
 */
void visit_ast_object_init(AST_object_init* node, outputbuffer* opb) {
    buff(opb, "constructor");
    visit((AST*)node->function_call, opb);
}

/**
 * Visitor for AST_attribute_access node
 *
 * @param AST_attribute_access* node
 * @param outputbuffer* opb
 */
void visit_ast_attribute_access(AST_attribute_access* node, outputbuffer* opb) {
    visit(node->left, opb);
    buff(opb, "->");
    if (node->right->type == AST_FUNCTION_CALL) {
        AST_function_call* fc = (AST_function_call*) node->right;
        fc->self = (AST*) init_ast_variable(init_token(TOKEN_ID, node->left->token->value));
    }
    visit(node->right, opb);
}

/**
 * Visitor for AST_variable node
 *
 * @param AST_variable* node
 * @param outputbuffer* opb
 */
void visit_ast_variable(AST_variable* node, outputbuffer* opb) {
    AST* a = (AST*) node;

    if (strcmp(a->token->value, "this") == 0) {
        buff(opb, "self");
    } else {
        buff(opb, ((AST*)node)->token->value);
    }
}

/**
 * Visitor for AST_assignment node
 *
 * @param AST_assignment* node
 * @param outputbuffer* opb
 */
void visit_ast_assignment(AST_assignment* node, outputbuffer* opb) {
    visit(node->left, opb);
    buff(opb, " = ");
    visit(node->right, opb);
}

/**
 * Visitor for AST_while node
 * 
 * @param AST_while* node
 * @param outputbuffer* opb
 */
void visit_ast_while(AST_while* node, outputbuffer* opb) {
    buff(opb, "while (");
    visit((AST*) node->expr, opb);
    buff(opb, ") {\n");
    visit((AST*) node->compound, opb);
    buff(opb, "\n}");
}
