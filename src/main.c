#include <stdio.h>
#include "include/token.h"
#include "include/io.h"
#include "include/lex.h"
#include "include/parse.h"


int main(int argc, char* argv[]) {
    char* contents = read_file(argv[1]);
    lexer* l = init_lexer(contents);
    parser* p = init_parser(l);

    parser_parse(p);

    return 0;
}
