#include "include/parse.h"
#include "include/dynamic_list.h"
#include <stdlib.h>
#include <stdio.h>


parser* init_parser(lexer* l) {
    parser* p = calloc(1, sizeof(struct PARSER_STRUCT));
    p->l = l;
    p->current_token = lexer_get_next_token(p->l);

    return p;
}

void parser_eat(parser* p, int token_type) {
    if (p->current_token->type != token_type) {
        printf("Unexpected token_type in parser: `%d`\n", token_type);
        exit(1);
    } else {
        p->current_token = lexer_get_next_token(p->l);
    }
}

AST* parser_parse(parser* p) {
    return parser_parse_compound(p);
}

AST* parser_parse_compound(parser* p) {
    dynamic_list* children = init_dynamic_list(sizeof(struct AST_STRUCT));
    AST* statement = parser_parse_statement(p);
}

AST* parser_parse_statement(parser* p) {

}
