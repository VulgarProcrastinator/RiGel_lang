#include <stdint.h>
#include <stdio.h>

#include "chunk.h"
#include "debug.h"

static int simpleInstraction(const char* name, int offcet){
    printf("%s\n", name);
    return offcet +1;
}

int disassembleInstraction(Chunk *chunk, int offcet){
    printf("%04d ",offcet);
    // %04d is shit to have if you want your output have 
    // 4 number before, so like 0001 0002 and stuff
    
    uint8_t instruction = chunk->code[offcet];
    switch (instruction){
        case OP_RETURN:
            return simpleInstraction("OP_RETURN", offcet);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offcet +1; 
    }
}


void disassembleChunk(Chunk *chunk, const char* name){
    printf("== %s ==\n", name);

    for (int offcet =0; offcet < chunk->count;){
        offcet = disassembleInstraction(chunk, offcet);
    }
};
