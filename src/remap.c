#include "include/remap.h"
#include <string.h>


const char* remap_function(const char* name, outputbuffer* opb) {
    if (strcmp(name, "print") == 0) {
        outputbuffer_require(opb, "<stdio.h>");
        return "printf";
    }

    return name;
}
