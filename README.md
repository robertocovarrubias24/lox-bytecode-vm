# Lox Bytecode Virtual Machine

CPSC 323 Project 2 - Compilers and Languages

## Overview

This project implements a simple bytecode virtual machine for a subset of the Lox language. Instead of directly interpreting an AST, the program compiles source code into a flat chunk of bytecode instructions, then executes those instructions using a stack-based VM.

## Features Implemented

- Linear bytecode chunk
- Opcode instruction set
- Constant pool
- Stack-based execution
- Fetch-decode-execute VM loop
- Instruction pointer
- Disassembler mode using `-d`
- Arithmetic expressions
- Grouping with parentheses
- Print statements
- `.lox` file input

## Build

```bash
make