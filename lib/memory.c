#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize){
    if (newSize == 0){
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, newSize);
    // it's cool that when old size is 0 realloc would be like malloc
    if (result == NULL) exit(1);
    return result;

};
