#include "include/strutils.h"
#include <stdlib.h>
#include <string.h>


char* str_replace(char *sentence, char *find, char *replace) {
    char *dest = malloc(strlen(sentence)-strlen(find)+strlen(replace)+1);
    char *destptr = dest;

    *dest = 0;

    while (*sentence)
    {
        if (!strncmp(sentence, find, strlen(find)))
        {
            strcat (destptr, replace);
            sentence += strlen(find);
            destptr += strlen(replace);
        } else
        {
            *destptr = *sentence;
            destptr++;
            sentence++;
        }
    }
    *destptr = 0;
    return dest;
}
