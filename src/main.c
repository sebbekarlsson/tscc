#include <stdio.h>
#include "include/io.h"
#include "include/lex.h"
#include "include/token.h"


int main(int argc, char* argv[]) {
    char* contents = read_file(argv[1]);
    lexer* l = init_lexer(contents);

    token* a = lexer_get_next_token(l);
    printf("%s\n", a->value);

    while (a->type != TOKEN_EOF) {
        a = lexer_get_next_token(l);
        printf("%s\n", a->value);
    }

    return 0;
}
