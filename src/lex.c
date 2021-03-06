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
    if (l->current_char != '\0') {
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
    while (lexer_is_whitespace(l))
        lexer_advance(l);
}

/**
 * Check with the lexer instance if the current token is a whitespace 
 *
 * @param lexer* l 
 * 
 * @return int
 */
int lexer_is_whitespace(lexer* l) {
	return l->current_char == ' ' || (int)l->current_char == 10 || l->current_char == '\r';
}

/**
 * Collects an identifier
 *
 * @return token*
 */
token* lexer_collect_id(lexer* l) {
    int type = TOKEN_ID;

    char* buffer = calloc(2, sizeof(char));
    buffer[0] = l->current_char;
    buffer[1] = '\0';

    lexer_advance(l);

    while (isalnum(l->current_char)) {
        char* current_char_str = calloc(2, sizeof(char));
        current_char_str[0] = l->current_char;
        current_char_str[1] = '\0';

        buffer = realloc(buffer, (strlen(buffer) + 2) * sizeof(char));

        strcat(buffer, current_char_str);
        free(current_char_str);

        lexer_advance(l);
    }

	if (strcmp(buffer, "function") == 0)
	    type = TOKEN_FUNCTION_TYPE;
	else if (strcmp(buffer, "number") == 0)
	    type = TOKEN_INTEGER_TYPE;
	else if (strcmp(buffer, "string") == 0)
	    type = TOKEN_STRING_TYPE;
	else if (strcmp(buffer, "void") == 0)
	    type = TOKEN_VOID_TYPE;
	else if (strcmp(buffer, "null") == 0)
	    type = TOKEN_NULL_TYPE;
	else if (strcmp(buffer, "undefined") == 0)
	    type = TOKEN_UNDEFINED_TYPE;
    else if (strcmp(buffer, "i32") == 0)
	    type = TOKEN_i32_TYPE;
	else if (strcmp(buffer, "let") == 0)
	    type = TOKEN_LET;
    else if (strcmp(buffer, "var") == 0)
	    type = TOKEN_VAR;
	else if (strcmp(buffer, "if") == 0)
	    type = TOKEN_IF;
	else if (strcmp(buffer, "else") == 0)
	    type = TOKEN_ELSE;
	else if (strcmp(buffer, "class") == 0)
	    type = TOKEN_CLASS_TYPE;
	else if (strcmp(buffer, "new") == 0)
	    type = TOKEN_NEW;
	else if (strcmp(buffer, "while") == 0)
	    type = TOKEN_WHILE;
	else if (strcmp(buffer, "return") == 0)
	    type = TOKEN_RETURN;
    else if (strcmp(buffer, "for") == 0)
	    type = TOKEN_FOR;

    return init_token(type, buffer);
}

/**
 * Collects a string starting with " and ending with "
 *
 * @return token*
 */
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

        buffer = realloc(buffer, (strlen(buffer) + 2) * sizeof(char));

        strcat(buffer, current_char_str);
        free(current_char_str);

        lexer_advance(l);
    }

    lexer_advance(l);

    return init_token(TOKEN_STRING_VALUE, buffer); 
}

/**
 * Collects a comment.
 *
 * @return token*
 */
token* lexer_collect_comment(lexer* l) {
    char* buffer = calloc(2, sizeof(char));

    char startchar = l->current_char;
    
    lexer_advance(l);

    buffer[0] = l->current_char;
    buffer[1] = '\0';

    while (1) {
        if (startchar == '/' && l->current_char == '\n') {
            lexer_advance(l);
            break;
        }

        if (startchar == '*' && l->current_char == '*') {
            lexer_advance(l);

            if (l->current_char == '/') {
                lexer_advance(l);
                break;
            }
        }

        char* current_char_str = calloc(2, sizeof(char));
        current_char_str[0] = l->current_char;
        current_char_str[1] = '\0';

        buffer = realloc(buffer, (strlen(buffer) + 2) * sizeof(char));

        strcat(buffer, current_char_str);
        free(current_char_str);

        lexer_advance(l); 
    }

    return init_token(TOKEN_COMMENT_VALUE, buffer); 
}

/**
 * Collects a number
 *
 * @return token*
 */
token* lexer_collect_number(lexer* l) {
    char* buffer = calloc(2, sizeof(char));

    int type = TOKEN_INTEGER_VALUE;

    buffer[0] = l->current_char;
    buffer[1] = '\0';
    
    char* current_char_str = calloc(1, sizeof(char));
    current_char_str[0] = '\0';

    lexer_advance(l);

    while (isdigit(l->current_char)) {
        current_char_str[0] = l->current_char;
        current_char_str[1] = '\0';

        strcat(buffer, current_char_str);

        lexer_advance(l);
    }

    if (l->current_char == '.') {
        free(current_char_str);
        current_char_str = calloc(2, sizeof(char));
        current_char_str[0] = l->current_char;
        current_char_str[1] = '\0';
        strcat(buffer, current_char_str);

        lexer_advance(l);
        type = TOKEN_FLOAT_VALUE;

        while (isdigit(l->current_char)) {
            free(current_char_str);
            current_char_str = calloc(2, sizeof(char));
            current_char_str[0] = l->current_char;
            current_char_str[1] = '\0';

            strcat(buffer, current_char_str);

            lexer_advance(l);
        }
    }

    return init_token(type, buffer); 
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
        if (lexer_is_whitespace(l))
            lexer_skip_whitespace(l);

		if (l->current_char == '\0')
			return init_token(TOKEN_EOF, "\0");

        if (isdigit(l->current_char))
            return lexer_collect_number(l);

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
            case '.': {
                token* t = init_token(TOKEN_DOT, current_char_str);
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
            case '+': {
                token* t = init_token(TOKEN_PLUS, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case '-': {
                token* t = init_token(TOKEN_MINUS, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case '/': {
                lexer_advance(l);
                if (l->current_char == '/' || l->current_char == '*')
                {
                    return lexer_collect_comment(l);
                }
                else
                {
                    return init_token(TOKEN_DIVIDE, current_char_str);
                }
            } break;
            case '*': {
                token* t = init_token(TOKEN_MULTIPLY, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case '<': {
                token* t = init_token(TOKEN_LESS_THAN, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case '>': {
                token* t = init_token(TOKEN_LARGER_THAN, current_char_str);
                lexer_advance(l);
                return t;
            } break;
            case '=': {
                int token_type = TOKEN_EQUALS;
                lexer_advance(l);
                if (l->current_char == '=') {
                    token_type = TOKEN_EQUALS_EQUALS;
                    token* t = init_token(token_type, "==");
                    lexer_advance(l);
                    return t;
                } else {
                    token* t = init_token(token_type, current_char_str);
                    return t; 
                }
            } break;
            case '!': {
                lexer_advance(l);
                if (l->current_char == '=') {
                    token*t = init_token(TOKEN_NOT_EQUALS, "!=");
                    lexer_advance(l);
                    return t;
                }
                lexer_advance(l);
            } break;
        }

        printf("The lexer did not expect `%s` (%d)\n", current_char_str, (int) l->current_char);
        exit(1);

        free(current_char_str);
    }

    return init_token(TOKEN_EOF, "\0");
}
