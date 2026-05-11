#include "compiler.h"
#include "scanner.h"
#include <cstdlib>
#include <iostream>

class Compiler {
private:
    Scanner scanner;
    Token current;
    Token previous;
    Chunk* chunk;
    bool hadError;

    void advance();
    bool check(TokenType type);
    bool match(TokenType type);
    void consume(TokenType type, const std::string& message);

    void emitByte(uint8_t byte);
    void emitReturn();
    void emitConstant(double value);

    void expression();
    void term();
    void factor();
    void unary();
    void primary();
    void statement();

public:
    Compiler(const std::string& source, Chunk& chunk);
    bool compile();
};

Compiler::Compiler(const std::string& source, Chunk& chunk)
    : scanner(source) {
    this->chunk = &chunk;
    hadError = false;
}

void Compiler::advance() {
    previous = current;

    for (;;) {
        current = scanner.scanToken();

        if (current.type != TOKEN_ERROR) {
            break;
        }

        std::cerr << "Error: " << current.lexeme << "\n";
        hadError = true;
    }
}

bool Compiler::check(TokenType type) {
    return current.type == type;
}

bool Compiler::match(TokenType type) {
    if (!check(type)) {
        return false;
    }

    advance();
    return true;
}

void Compiler::consume(TokenType type, const std::string& message) {
    if (current.type == type) {
        advance();
        return;
    }

    std::cerr << "Error: " << message << "\n";
    hadError = true;
}

void Compiler::emitByte(uint8_t byte) {
    chunk->write(byte);
}

void Compiler::emitReturn() {
    emitByte(OP_RETURN);
}

void Compiler::emitConstant(double value) {
    int constant = chunk->addConstant(value);
    emitByte(OP_CONSTANT);
    emitByte(constant);
}

void Compiler::expression() {
    term();
}

void Compiler::term() {
    factor();

    while (match(TOKEN_PLUS) || match(TOKEN_MINUS)) {
        TokenType operatorType = previous.type;
        factor();

        if (operatorType == TOKEN_PLUS) {
            emitByte(OP_ADD);
        } else {
            emitByte(OP_SUBTRACT);
        }
    }
}

void Compiler::factor() {
    unary();

    while (match(TOKEN_STAR) || match(TOKEN_SLASH)) {
        TokenType operatorType = previous.type;
        unary();

        if (operatorType == TOKEN_STAR) {
            emitByte(OP_MULTIPLY);
        } else {
            emitByte(OP_DIVIDE);
        }
    }
}

void Compiler::unary() {
    if (match(TOKEN_MINUS)) {
        unary();
        emitByte(OP_NEGATE);
    } else {
        primary();
    }
}

void Compiler::primary() {
    if (match(TOKEN_NUMBER)) {
        double value = std::stod(previous.lexeme);
        emitConstant(value);
        return;
    }

    if (match(TOKEN_LEFT_PAREN)) {
        expression();
        consume(TOKEN_RIGHT_PAREN, "Expected ')' after expression.");
        return;
    }

    std::cerr << "Error: Expected expression.\n";
    hadError = true;
}

void Compiler::statement() {
    if (match(TOKEN_PRINT)) {
        expression();
        consume(TOKEN_SEMICOLON, "Expected ';' after value.");
        emitByte(OP_PRINT);
        return;
    }

    expression();
    consume(TOKEN_SEMICOLON, "Expected ';' after expression.");
    emitByte(OP_POP);
}

bool Compiler::compile() {
    advance();

    while (!check(TOKEN_EOF)) {
        statement();
    }

    emitReturn();
    return !hadError;
}

bool compile(const std::string& source, Chunk& chunk) {
    Compiler compiler(source, chunk);
    return compiler.compile();
}