#ifndef TSCC_TOKEN_H
#define TSCC_TOKEN_H
typedef struct TOKEN_STRUCT {
    enum {
        TOKEN_EOF,
        TOKEN_ID,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_LBRACKET,
        TOKEN_RBRACKET,
        TOKEN_COLON,
        TOKEN_SEMI,
        TOKEN_COMMA,
        TOKEN_STRING_VALUE
    } type;

    char* value;
} token;

token* init_token(int type, char* value);
#endif
