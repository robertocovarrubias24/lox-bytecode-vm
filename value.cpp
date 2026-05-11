#include "value.h"

void printValue(const Value& value) {
    if (std::holds_alternative<double>(value)) {
        std::cout << std::get<double>(value);
    } else if (std::holds_alternative<bool>(value)) {
        std::cout << (std::get<bool>(value) ? "true" : "false");
    } else {
        std::cout << std::get<std::string>(value);
    }
}

bool isFalsey(const Value& value) {
    if (std::holds_alternative<bool>(value)) {
        return !std::get<bool>(value);
    }
    return false;
}

bool valuesEqual(const Value& a, const Value& b) {
    return a == b;
}