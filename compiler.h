#ifndef COMPILER_H
#define COMPILER_H

#include "chunk.h"
#include <string>

bool compile(const std::string& source, Chunk& chunk);

#endif