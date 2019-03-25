#ifndef TSCC_PARSE_H
#define TSCC_PARSE_H
#include "token.h"
#include "lex.h"
#include "AST.h"
typedef struct PARSER_STRUCT {
    token* current_token;
    lexer* l;
} parser;

parser* init_parser(lexer* l);

void parser_eat(parser* p, int token_type);

AST* parser_parse(parser* p);

AST* parser_parse_compound(parser* p);

AST* parser_parse_statement(parser* p);
#endif
