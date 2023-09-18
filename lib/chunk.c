#include <stdint.h>
#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk *chunk){
    chunk->capacity =0;
    chunk->count =0;
    chunk->code =NULL;
    initValueArray(&chunk->constants);
}
void freeChunk(Chunk *chunk){
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity){
        initValueArray(&chunk->constants);
        initChunk(chunk);
    }
}

void writeChunk(Chunk *chunk, uint8_t byte){
    if (chunk->capacity < chunk->count+1){
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
         oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value){
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count -1;
    // it's going to return the appended count, not the current one that is going to be +1 
}
