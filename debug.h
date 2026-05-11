#ifndef DEBUG_H
#define DEBUG_H

#include "chunk.h"
#include <string>

void disassembleChunk(const Chunk& chunk, const std::string& name);
int disassembleInstruction(const Chunk& chunk, int offset);

#endif