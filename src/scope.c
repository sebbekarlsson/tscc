#include "include/scope.h"
#include <stdlib.h>


scope* init_scope(AST* owner) {
    scope* s = calloc(1, sizeof(struct SCOPE_STRUCT));
    s->owner = owner;

    return s;
}
