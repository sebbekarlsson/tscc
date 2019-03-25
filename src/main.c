#include <stdio.h>
#include "include/token.h"
#include "include/io.h"
#include "include/lex.h"
#include "include/parse.h"
#include "include/visit.h"


int main(int argc, char* argv[]) {
    char* contents = read_file(argv[1]);
    lexer* l = init_lexer(contents);
    parser* p = init_parser(l);

    AST* tree = (AST*) parser_parse(p);
    visit(tree);

    return 0;
}
