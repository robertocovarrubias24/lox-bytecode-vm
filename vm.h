#ifndef VM_H
#define VM_H

#include "chunk.h"
#include <vector>

class VM {
private:
    Chunk* chunk;
    int ip;
    std::vector<Value> stack;

    uint8_t readByte();
    Value readConstant();

    void push(const Value& value);
    Value pop();

public:
    VM();

    void resetStack();
    bool interpret(Chunk& chunk);
};

#endif