#include "include/outputbuffer.h"
#include <string.h>
#include <stdio.h>


outputbuffer* init_outputbuffer() {
    outputbuffer* opb = calloc(1, sizeof(struct OUTPUTBUFFER_STRUCT));
    opb->buffer = calloc(1, sizeof(char));
    opb->buffer[0] = '\0';
    opb->requirements = init_dynamic_list(sizeof(char*));

    return opb;
}

void buff(outputbuffer* opb, const char* buffer) {
    opb->buffer = realloc(opb->buffer, (strlen(opb->buffer) + strlen(buffer)) * sizeof(char));
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
        char* incl = calloc(strlen("#include "), sizeof(char));
        incl[0] = '\0';
        strcat(incl, "#include ");
        incl = realloc(incl, (strlen(incl) + strlen((char*)opb->requirements->items[i])) * sizeof(char));
        strcat(incl, (char*)opb->requirements->items[i]);
        strcat(incl, "\n");
        strcat(output, incl);
        free(incl);
    }
    
    output = realloc(output, (strlen(output) + strlen(opb->buffer)) * sizeof(char));
    strcat(output, opb->buffer);
    
    return output;
}
