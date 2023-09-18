#include "lib/chunk.h"
#include "lib/common.h"
#include "lib/memory.h"
#include "lib/debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);
    
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
