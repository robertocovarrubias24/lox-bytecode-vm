#include "debug.h"
#include <iostream>
#include <iomanip>

static int simpleInstruction(const std::string& name, int offset) {
    std::cout << name << "\n";
    return offset + 1;
}

static int constantInstruction(const std::string& name, const Chunk& chunk, int offset) {
    uint8_t constant = chunk.code[offset + 1];

    std::cout << std::left << std::setw(16) << name
              << (int)constant << " '";

    printValue(chunk.constants[constant]);

    std::cout << "'\n";
    return offset + 2;
}

void disassembleChunk(const Chunk& chunk, const std::string& name) {
    std::cout << "== Disassembly: " << name << " ==\n";

    for (int offset = 0; offset < (int)chunk.code.size();) {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(const Chunk& chunk, int offset) {
    std::cout << std::right << std::setw(4) << std::setfill('0') << offset << " ";    std::cout << std::setfill(' ');
    uint8_t instruction = chunk.code[offset];

    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_NIL:
            return simpleInstruction("OP_NIL", offset);
        case OP_TRUE:
            return simpleInstruction("OP_TRUE", offset);
        case OP_FALSE:
            return simpleInstruction("OP_FALSE", offset);
        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_EQUAL:
            return simpleInstruction("OP_EQUAL", offset);
        case OP_GREATER:
            return simpleInstruction("OP_GREATER", offset);
        case OP_LESS:
            return simpleInstruction("OP_LESS", offset);
        case OP_NOT:
            return simpleInstruction("OP_NOT", offset);
        case OP_PRINT:
            return simpleInstruction("OP_PRINT", offset);
        case OP_POP:
            return simpleInstruction("OP_POP", offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            std::cout << "Unknown opcode " << (int)instruction << "\n";
            return offset + 1;
    }
}