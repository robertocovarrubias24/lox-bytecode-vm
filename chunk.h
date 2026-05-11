#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <cstdint>
#include "value.h"

enum OpCode {
    OP_CONSTANT,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_NOT,
    OP_PRINT,
    OP_POP,
    OP_RETURN
};

class Chunk {
public:
    std::vector<uint8_t> code;
    std::vector<Value> constants;

    void write(uint8_t byte);
    int addConstant(const Value& value);
};

#endif