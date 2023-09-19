#include "lib/chunk.h"
#include "lib/common.h"
#include "lib/memory.h"
#include "lib/debug.h"
#include "lib/vm.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
    initVM();  
    // try having vm as global variable
    //VM vm;  
    //vm.ip = NULL;

    Chunk chunk;
   
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    // addConstant returns constant count/place in array
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    int constant2 = addConstant(&chunk, 3.3);
    writeChunk(&chunk, OP_CONSTANT, 124);
    writeChunk(&chunk, constant2, 124);
    writeChunk(&chunk, OP_RETURN, 124);
    
    disassembleChunk(&chunk, "test chunk");
    printf("<><><><><><><><>><>><><><><><><><><><><>\n");
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);

    return 0;
}
