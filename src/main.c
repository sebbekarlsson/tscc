#include <stdio.h>
#include "include/token.h"
#include "include/io.h"
#include "include/lex.h"
#include "include/parse.h"
#include "include/visit.h"
#include "include/outputbuffer.h"


int main(int argc, char* argv[]) {
    char* contents = read_file(argv[1]);
    lexer* l = init_lexer(contents);
    parser* p = init_parser(l);

    AST* tree = (AST*) parser_parse(p);
    
    outputbuffer* opb = init_outputbuffer();

    visit(tree, opb);

    char* output = outputbuffer_get(opb);

    printf(output);
    free(output);

    free(contents);
    free(opb->buffer);

    free(opb->requirements->items);
    free(opb->requirements);
    free(opb);

    free(p->current_token);
    free(p);
    free(l);
    free(tree);

    return 0;
}
