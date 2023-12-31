#include <stdio.h>
#include "chunk.h"
#include "debug.h"

static int simpleInstraction(const char* name, int offset){
    printf("%s\n", name);
    return offset +1;
}
static int constantInstraction(const char* name, Chunk* chunk, int offset){
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("' \n");
    return offset +2;
}

int disassembleInstraction(Chunk *chunk, int offset){
    printf("%04d ",offset);
    // %04d is shit to have if you want your output have 
    // 4 number before, so like 0001 0002 and stuff

    if (offset > 0 &&
     chunk->lines[offset] == chunk->lines[offset -1]){
        printf("    | ");
    }else {
        printf("%4d ",chunk->lines[offset]);
    } 

    uint8_t instruction = chunk->code[offset];
    switch (instruction){
        case OP_CONSTANT:
            return constantInstraction("OP_CONSTANT", chunk, offset);
        case OP_ADD:
            return simpleInstraction("OP_ADD", offset);        
        case OP_SUBTRACT:
            return simpleInstraction("OP_SUBTRACT", offset);        
        case OP_MULTIPLY:
            return simpleInstraction("OP_MULTIPLY", offset);        
        case OP_DIVIDE:
            return simpleInstraction("OP_DIVIDE", offset);        
        case OP_NEGATE:
            return simpleInstraction("OP_NEGATE", offset);
        case OP_RETURN:
            return simpleInstraction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset +1; 
    }
}


void disassembleChunk(Chunk *chunk, const char* name){
    printf("== %s ==\n", name);

    for (int offset =0; offset < chunk->count;){
        offset = disassembleInstraction(chunk, offset);
    }
};
