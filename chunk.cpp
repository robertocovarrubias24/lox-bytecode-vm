#include "chunk.h"

void Chunk::write(uint8_t byte) {
    code.push_back(byte);
}

int Chunk::addConstant(const Value& value) {
    constants.push_back(value);
    return constants.size() - 1;
}