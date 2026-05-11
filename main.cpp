#include "chunk.h"
#include "compiler.h"
#include "debug.h"
#include "vm.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static std::string readFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << path << "\n";
        exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    bool debugMode = false;
    std::string fileName;

    if (argc == 2) {
        fileName = argv[1];
    } else if (argc == 3 && std::string(argv[1]) == "-d") {
        debugMode = true;
        fileName = argv[2];
    } else {
        std::cout << "Usage: ./loxvm [-d] file.lox\n";
        return 1;
    }

    std::string source = readFile(fileName);

    Chunk chunk;

    if (!compile(source, chunk)) {
        return 1;
    }

    if (debugMode) {
        disassembleChunk(chunk, fileName);
        return 0;
    }

    VM vm;
    vm.interpret(chunk);

    return 0;
}