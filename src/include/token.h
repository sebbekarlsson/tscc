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
        TOKEN_DOT,
        TOKEN_LET,
        TOKEN_VAR,
        TOKEN_EQUALS,
        TOKEN_EQUALS_EQUALS,
        TOKEN_NOT_EQUALS,
        TOKEN_LARGER_THAN,
        TOKEN_LESS_THAN,
        TOKEN_STRING_TYPE,
        TOKEN_INTEGER_TYPE,
        TOKEN_VOID_TYPE,
        TOKEN_VOID_POINTER_TYPE,
        TOKEN_STRING_VALUE,
        TOKEN_INTEGER_VALUE,
        TOKEN_FLOAT_VALUE,
        TOKEN_COMMENT_VALUE,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_DIVIDE,
        TOKEN_MULTIPLY,
        TOKEN_FUNCTION_TYPE,
        TOKEN_IF,
        TOKEN_ELSE,
        TOKEN_NULL_TYPE,
        TOKEN_UNDEFINED_TYPE,
        TOKEN_i32_TYPE,
        TOKEN_CLASS_TYPE,
        TOKEN_NEW,
        TOKEN_WHILE,
        TOKEN_FOR,
        TOKEN_RETURN
    } type;

    char* value;
} token;

token* init_token(int type, char* value);
#endif
