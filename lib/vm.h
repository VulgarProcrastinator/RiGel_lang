#ifndef rigel_vm_h
#define rigel_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    // ip - instraction pointer
    uint8_t* ip;
    Value stack[STACK_MAX];
    // always points past the last item, like it is pointing to whare the next item is going to be
    Value* stackTOP;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif