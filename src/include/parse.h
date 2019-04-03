#ifndef TSCC_PARSE_H
#define TSCC_PARSE_H
#include "token.h"
#include "lex.h"
#include "AST.h"
#include "scope.h"
#include "ASTCompound.h"
#include "ASTBinop.h"
#include "ASTInteger.h"
#include "ASTFloat.h"
#include "ASTString.h"
#include "ASTDatatype.h"
#include "ASTFunctionDefinition.h"
#include "ASTVariableDefinition.h"
#include "ASTFunctionCall.h"
#include "ASTIf.h"
#include "ASTNull.h"
#include "ASTClass.h"
#include "ASTUndefined.h"
#include "ASTObjectInit.h"
#include "ASTVariable.h"
#include "ASTAttributeAccess.h"
#include "ASTAssignment.h"
#include "ASTWhile.h"

typedef struct PARSER_STRUCT {
    token* current_token;
    lexer* l;
} parser;

parser* init_parser(lexer* l);

void parser_eat(parser* p, int token_type);

AST_compound* parser_parse(parser* p, scope* s);

AST_compound* parser_parse_compound(parser* p, scope* s);

AST* parser_parse_statement(parser* p, scope* s);

AST* parser_parse_expr(parser* p, scope* s);

AST* parser_parse_term(parser* p, scope* s);

AST* parser_parse_factor(parser* p, scope* s);

AST_function_definition* parser_parse_function_definition(parser* p, scope* s);

AST_variable_definition* parser_parse_variable_definition(parser* p, scope* s);

AST_datatype* parser_parse_data_type(parser* p, scope* s);

AST* parser_parse_id(parser* p, scope* s);

AST_function_call* parser_parse_function_call(parser* p, scope* s, token* t);

AST_if* parser_parse_if(parser* p, scope* s);

AST_class* parser_parse_class(parser* p, scope* s);

AST_object_init* parser_parse_object_init(parser* p, scope* s);

AST_while* parser_parse_while(parser* p, scope* s);
#endif
