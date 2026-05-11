#include "vm.h"
#include <iostream>

#define BINARY_OP(op) \
    do { \
        double b = std::get<double>(pop()); \
        double a = std::get<double>(pop()); \
        push(a op b); \
    } while (false)

VM::VM() {
    chunk = nullptr;
    ip = 0;
}

void VM::resetStack() {
    stack.clear();
}

uint8_t VM::readByte() {
    return chunk->code[ip++];
}

Value VM::readConstant() {
    return chunk->constants[readByte()];
}

void VM::push(const Value& value) {
    stack.push_back(value);
}

Value VM::pop() {
    Value value = stack.back();
    stack.pop_back();
    return value;
}

bool VM::interpret(Chunk& inputChunk) {
    chunk = &inputChunk;
    ip = 0;

    for (;;) {
        uint8_t instruction = readByte();

        switch (instruction) {
            case OP_CONSTANT:
                push(readConstant());
                break;

            case OP_NIL:
                push(false);
                break;

            case OP_TRUE:
                push(true);
                break;

            case OP_FALSE:
                push(false);
                break;

            case OP_ADD:
                BINARY_OP(+);
                break;

            case OP_SUBTRACT:
                BINARY_OP(-);
                break;

            case OP_MULTIPLY:
                BINARY_OP(*);
                break;

            case OP_DIVIDE:
                BINARY_OP(/);
                break;

            case OP_NEGATE:
                push(-std::get<double>(pop()));
                break;

            case OP_EQUAL: {
                Value b = pop();
                Value a = pop();
                push(valuesEqual(a, b));
                break;
            }

            case OP_GREATER:
                BINARY_OP(>);
                break;

            case OP_LESS:
                BINARY_OP(<);
                break;

            case OP_NOT:
                push(isFalsey(pop()));
                break;

            case OP_PRINT:
                printValue(pop());
                std::cout << "\n";
                break;

            case OP_POP:
                pop();
                break;

            case OP_RETURN:
                return true;
        }
    }
}