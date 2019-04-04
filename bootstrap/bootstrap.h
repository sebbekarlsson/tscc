#include <stdlib.h>


typedef struct DYNAMIC_LIST_STRUCT {
    size_t size;
    size_t item_size;
    void** items;
} dynamic_list;

dynamic_list* init_dynamic_list(size_t item_size) {
    dynamic_list* dlist = calloc(1, sizeof(struct DYNAMIC_LIST_STRUCT));
    dlist->item_size = item_size;
    dlist->size = 0;

    return dlist;
}

void dynamic_list_append(dynamic_list* dlist, void* item) {
    dlist->size++;
    dlist->items = realloc(dlist->items, (dlist->size + 1) * dlist->item_size);
    dlist->items[dlist->size - 1] = item;
}

void dynamic_list_free(dynamic_list* dlist) {}

typedef struct CONSOLE_STRUCT {
    void* (*log)(void* self, char* inp);
} console_t;

void console_log(console_t* console, char* inp) {
    printf(inp);
}

console_t* init_console() {
    console_t* console = calloc(1, sizeof(struct CONSOLE_STRUCT));
    console->log = console_log;
    return console;
}

console_t* console;


char charAt(char* value, int index) {
    return value[index];
}


void bootstrap() {
    console = init_console();
}
