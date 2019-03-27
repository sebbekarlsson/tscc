#ifndef TSCC_OUTPUTBUFFER_H
#define TSCC_OUTPUTBUFFER_H
#include "dynamic_list.h"
typedef struct OUTPUTBUFFER_STRUCT {
    char* buffer;
    dynamic_list* requirements;
} outputbuffer;

outputbuffer* init_outputbuffer();

void buff(outputbuffer* opb, const char* buffer);

void outputbuffer_require(outputbuffer* opb, char* requirement);

char* outputbuffer_get(outputbuffer* opb);
#endif
