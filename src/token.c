#include "include/token.h"
#include <stdlib.h>


token* init_token(int type, char* value) {
    token* t = calloc(1, sizeof(struct TOKEN_STRUCT));
    t->type = type;
    t->value = value;

    return t;
}
