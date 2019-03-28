#ifndef TSCC_AST_CLASS_H
#define TSCC_AST_CLASS_H
#include "AST.h"
#include "dynamic_list.h"

typedef struct AST_CLASS_STRUCT {
    AST base;
    char* name;
    dynamic_list* variable_definitions;
    dynamic_list* function_definitions;
} AST_class;

AST_class* init_ast_class(token* t, char* name, dynamic_list* variable_definitions, dynamic_list* function_definitions);
#endif
