#ifndef TSCC_PARSE_H
#define TSCC_PARSE_H
#include "token.h"
#include "lex.h"
#include "AST.h"
#include "ASTCompound.h"
#include "ASTBinop.h"
#include "ASTInteger.h"
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
#endif
