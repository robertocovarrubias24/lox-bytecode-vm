#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <variant>

using Value = std::variant<double, bool, std::string>;

void printValue(const Value& value);
bool isFalsey(const Value& value);
bool valuesEqual(const Value& a, const Value& b);

#endif