#include "include/remap.h"
#include <string.h>


const char* remap_function(const char* name) {
    if (strcmp(name, "print") == 0)
        return "printf";

    return name;
}
