#include "include/lex.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


/**
 * Initialize a new lexer instance
 *
 * @return lexer*
 */
lexer* init_lexer(char* contents) {
    lexer* l = calloc(1, sizeof(struct LEXER_STRUCT));
    l->contents = contents;
    l->pointer = 0;
    l->current_char = contents[l->pointer];

    return l;
}

/**
 * Advance the current position of a lexer instance if possible.
 *
 * @param lexer* l
 */
void lexer_advance(lexer* l) {
    if (l->current_char != '\0' && l->pointer < strlen(l->contents)) {
        l->pointer += 1;
        l->current_char = l->contents[l->pointer];
    }
}

/**
 * Skip whitespace for a lexer instance until there is no whitespace.
 *
 * @param lexer* l
 */
void lexer_skip_whitespace(lexer* l) {
    while (l->current_char == ' ' || (int)l->current_char == 10)
        lexer_advance(l);
}

token* lexer_collect_id(lexer* l) {
    char* buffer = calloc(2, sizeof(char));
    buffer[0] = l->current_char;
    buffer[1] = '\0';

    lexer_advance(l);

    while (isalnum(l->current_char)) {
        char* current_char_str = calloc(2, sizeof(char));
        current_char_str[0] = l->current_char;
        current_char_str[1] = '\0';

        strcat(buffer, current_char_str);

        lexer_advance(l);
    }

    return init_token(TOKEN_ID, buffer);
}

token* lexer_collect_string(lexer* l) {
    char* buffer = calloc(2, sizeof(char));

    lexer_advance(l);

    buffer[0] = l->current_char;
    buffer[1] = '\0';

    lexer_advance(l);

    while (l->current_char != '"') {
        char* current_char_str = calloc(2, sizeof(char));
        current_char_str[0] = l->current_char;
        current_char_str[1] = '\0';

        strcat(buffer, current_char_str);

        lexer_advance(l);
    }

    lexer_advance(l);

    return init_token(TOKEN_STRING_VALUE, buffer); 
}

/**
 * Receive the next token of the lexer instance
 *
 * @param lexer* l
 *
 * @return token*
 */
token* lexer_get_next_token(lexer* l) {
    while (l->current_char != '\0' && l->pointer < strlen(l->contents) - 1) {
        if (l->current_char == ' ' || (int)l->current_char == 10)
            lexer_skip_whitespace(l);

        if (isalnum(l->current_char))
            return lexer_collect_id(l);

        char* current_char_str = calloc(2, sizeof(char));
        current_char_str[0] = l->current_char;
        current_char_str[1] = '\0';

        switch (l->current_char) {
            case '(': {
                token* t = init_token(TOKEN_LPAREN, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case ')': {
                token* t = init_token(TOKEN_RPAREN, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case ':': {
                token* t = init_token(TOKEN_COLON, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case ',': {
                token* t = init_token(TOKEN_COMMA, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case '[': {
                token* t = init_token(TOKEN_LBRACKET, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case ']': {
                token* t = init_token(TOKEN_RBRACKET, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case '{': {
                token* t = init_token(TOKEN_LBRACE, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case '}': {
                token* t = init_token(TOKEN_RBRACE, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case '"': {
                return lexer_collect_string(l);
            } break;
            case ';': {
                token* t = init_token(TOKEN_SEMI, current_char_str);
                lexer_advance(l);
                return t;
            } break;

        }

        printf("The lexer did not expect `%s` (%d)\n", current_char_str, (int) l->current_char);
        exit(1);

        free(current_char_str);
    }

    return init_token(TOKEN_EOF, "\0");
}
