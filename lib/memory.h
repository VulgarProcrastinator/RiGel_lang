#ifndef rigel_memory_h
#define rigel_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity)\
    ((capacity)< 8 ?  8 : (capacity) *2)
#define GROW_ARRAY(type, pointer,oldCount,newCount)\
    (type*)reallocate(pointer, sizeof(type) *(oldCount), \
        sizeof(type)* (newCount))
#define FREE_ARRAY(type, pointer, oldCapacity)\
    reallocate(pointer, sizeof(type)* oldCapacity, 0);

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif

