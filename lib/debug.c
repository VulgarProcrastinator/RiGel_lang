#include <stdint.h>
#include <stdio.h>

#include "chunk.h"
#include "debug.h"
#include "value.h"

static int simpleInstraction(const char* name, int offcet){
    printf("%s\n", name);
    return offcet +1;
}
static int constantInstraction(const char* name, Chunk* chunk, int offcet){
    uint8_t constant = chunk->code[offcet + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("' \n");
    return offcet +2;
}

int disassembleInstraction(Chunk *chunk, int offcet){
    printf("%04d ",offcet);
    // %04d is shit to have if you want your output have 
    // 4 number before, so like 0001 0002 and stuff
    
    uint8_t instruction = chunk->code[offcet];
    switch (instruction){
        case OP_RETURN:
            return simpleInstraction("OP_RETURN", offcet);
        case OP_CONSTANT:
            return constantInstraction("OP_CONSTANT", chunk, offcet);
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
