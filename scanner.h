#ifndef SCANNER_H
#define SCANNER_H

#include <string>

enum TokenType {
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR, TOKEN_SLASH,
    TOKEN_GREATER, TOKEN_LESS,
    TOKEN_SEMICOLON,
    TOKEN_NUMBER,
    TOKEN_PRINT,
    TOKEN_EOF,
    TOKEN_ERROR
};

struct Token {
    TokenType type;
    std::string lexeme;
};

class Scanner {
private:
    std::string source;
    int start;
    int current;

    bool isAtEnd();
    char advance();
    char peek();
    void skipWhitespace();

    Token makeToken(TokenType type);
    Token errorToken(const std::string& message);
    Token number();
    Token identifier();

public:
    Scanner(const std::string& source);
    Token scanToken();
};

#endif