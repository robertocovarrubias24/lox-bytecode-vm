#include "scanner.h"
#include <cctype>

Scanner::Scanner(const std::string& source) {
    this->source = source;
    start = 0;
    current = 0;
}

bool Scanner::isAtEnd() {
    return current >= (int)source.length();
}

char Scanner::advance() {
    return source[current++];
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

void Scanner::skipWhitespace() {
    for (;;) {
        char c = peek();

        switch (c) {
            case ' ':
            case '\r':
            case '\t':
            case '\n':
                advance();
                break;
            default:
                return;
        }
    }
}

Token Scanner::makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.lexeme = source.substr(start, current - start);
    return token;
}

Token Scanner::errorToken(const std::string& message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.lexeme = message;
    return token;
}

Token Scanner::number() {
    while (isdigit(peek())) {
        advance();
    }

    if (peek() == '.') {
        advance();

        while (isdigit(peek())) {
            advance();
        }
    }

    return makeToken(TOKEN_NUMBER);
}

Token Scanner::identifier() {
    while (isalpha(peek())) {
        advance();
    }

    std::string text = source.substr(start, current - start);

    if (text == "print") {
        return makeToken(TOKEN_PRINT);
    }

    return errorToken("Unexpected identifier.");
}

Token Scanner::scanToken() {
    skipWhitespace();

    start = current;

    if (isAtEnd()) {
        return makeToken(TOKEN_EOF);
    }

    char c = advance();

    if (isdigit(c)) {
        return number();
    }

    if (isalpha(c)) {
        return identifier();
    }

    switch (c) {
        case '(':
            return makeToken(TOKEN_LEFT_PAREN);
        case ')':
            return makeToken(TOKEN_RIGHT_PAREN);
        case '+':
            return makeToken(TOKEN_PLUS);
        case '-':
            return makeToken(TOKEN_MINUS);
        case '*':
            return makeToken(TOKEN_STAR);
        case '/':
            return makeToken(TOKEN_SLASH);
        case ';':
            return makeToken(TOKEN_SEMICOLON);
    }

    return errorToken("Unexpected character.");
}