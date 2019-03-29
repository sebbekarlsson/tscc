#include "include/AST.h"


void AST_constructor(AST* ast, token* t, int type) {
    ast->token = t;
    ast->type = type;
    ast->s = (void*) 0;
}
