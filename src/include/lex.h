#ifndef TSCC_LEX_H
#define TSCC_LEX_H
#include "token.h"

typedef struct LEXER_STRUCT {
    char* contents;
    char current_char;
    int pointer;
} lexer;

lexer* init_lexer(char* contents);

void lexer_advance(lexer* l);

void lexer_skip_whitespace(lexer* l);

token* lexer_collect_id(lexer* l);

token* lexer_collect_string(lexer* l);

token* lexer_get_next_token(lexer* l);
#endif
