#ifndef rigel_debug_h
#define rigel_debug_h

#include "chunk.h"

void disassembleChunk(Chunk *chunk, const char* name);
int disassembleInstraction(Chunk *chunk, int offset);

#endif

