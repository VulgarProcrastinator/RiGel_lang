#include "lib/chunk.h"
#include "lib/common.h"
#include "lib/memory.h"
#include "lib/debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
   
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    // addConstant returns constant count/place in array
    writeChunk(&chunk, OP_CONSTANT);
    writeChunk(&chunk, constant);
    writeChunk(&chunk, OP_RETURN);
    
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
