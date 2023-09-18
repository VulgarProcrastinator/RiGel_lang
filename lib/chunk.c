#include <stdint.h>
#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk){
    // remember that we use pointer because we don't want to make a coppy
    chunk->capacity = 0;
    //(*chunk).capacity =0; // don't forget that struct is a pointer and -> is basically
    // you looking though bits that wehere allocated to types the same way you would do int array
    chunk->count = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    // cunk->constants is a value(pointer)
    // & before it to get to is't value(insides) and not make coppy instead
    initValueArray(&chunk->constants);
}
void freeChunk(Chunk *chunk){
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity)
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}


void writeChunk(Chunk *chunk, uint8_t byte, int line){
    if (chunk->capacity < chunk->count+1){
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
            oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines,
            oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    // line number corrisponding with chunk's code
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value){
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count -1;
    // it's going to return the appended count, not the current one that is going to be +1 
}
