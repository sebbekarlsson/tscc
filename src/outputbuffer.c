#include "include/outputbuffer.h"
#include <string.h>
#include <stdio.h>


outputbuffer* init_outputbuffer() {
    outputbuffer* opb = calloc(1, sizeof(struct OUTPUTBUFFER_STRUCT));
    opb->buffer = calloc(2, sizeof(char));
    opb->buffer[0] = '\0';
    opb->requirements = init_dynamic_list(sizeof(char*));

    return opb;
}

void buff(outputbuffer* opb, const char* buffer) {
    size_t final_size = strlen(opb->buffer) + strlen(buffer) + 2;

    opb->buffer = realloc(opb->buffer, final_size * sizeof(char));
    strcat(opb->buffer, buffer);
}

void outputbuffer_require(outputbuffer* opb, char* requirement) {
    for (int i = 0; i < opb->requirements->size; i++)
        if (strcmp((char*)opb->requirements->items[i], requirement) == 0)
            return;

    dynamic_list_append(opb->requirements, requirement);
}

char* outputbuffer_get(outputbuffer* opb) {
    char* output = calloc(1, sizeof(char));
    output[0] = '\0';

    for (int i = 0; i < opb->requirements->size; i++) {
        char* incl = calloc(strlen("#include ") + 1, sizeof(char));
        incl[0] = '\0';
        strcat(incl, "#include ");
        incl = realloc(incl, (strlen(incl) + 2 + strlen((char*)opb->requirements->items[i])) * sizeof(char));
        strcat(incl, (char*)opb->requirements->items[i]);
        strcat(incl, "\n");
        output = realloc(output, (strlen(output) + 2 + strlen(incl)) * sizeof(char));
        strcat(output, incl);
        free(incl);
    }
    
    output = realloc(output, (strlen(output) + 2 + strlen(opb->buffer)) * sizeof(char));
    strcat(output, opb->buffer);
    
    return output;
}
