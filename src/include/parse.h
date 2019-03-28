#ifndef TSCC_PARSE_H
#define TSCC_PARSE_H
#include "token.h"
#include "lex.h"
#include "AST.h"
#include "ASTCompound.h"
#include "ASTBinop.h"
#include "ASTInteger.h"
#include "ASTString.h"
#include "ASTDatatype.h"
#include "ASTFunctionDefinition.h"
#include "ASTVariableDefinition.h"
#include "ASTFunctionCall.h"
#include "ASTIf.h"
#include "ASTNull.h"
#include "ASTClass.h"
#include "ASTUndefined.h"


typedef struct PARSER_STRUCT {
    token* current_token;
    lexer* l;
} parser;

parser* init_parser(lexer* l);

void parser_eat(parser* p, int token_type);

AST_compound* parser_parse(parser* p);

AST_compound* parser_parse_compound(parser* p);

AST* parser_parse_statement(parser* p);

AST* parser_parse_expr(parser* p);

AST* parser_parse_term(parser* p);

AST* parser_parse_factor(parser* p);

AST_function_definition* parser_parse_function_definition(parser* p);

AST_variable_definition* parser_parse_variable_definition(parser* p);

AST_datatype* parser_parse_data_type(parser* p);

AST* parser_parse_id(parser* p);

AST_function_call* parser_parse_function_call(parser* p, token* t);

AST_if* parser_parse_if(parser* p);

AST_class* parser_parse_class(parser* p);
#endif
