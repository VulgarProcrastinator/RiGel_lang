#ifndef rigel_chunk_h
#define rigel_chunk_h

#include "common.h"
#include "value.h"

// future instraction for VM that will mean
// return from the current function
typedef enum{
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
} OpCode;

// a dynmic array of instactions
// because bytecode is series of instractions we need a place to store it all
typedef struct{
    int count;
    int capacity;
    uint8_t* code; // basicaly an array , remember arrays are pointers
    int* lines;
    // struct inside a struct
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);

#endif