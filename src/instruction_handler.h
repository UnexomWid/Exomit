/**
 * X10 (https://github.com/UnexomWid/X10)
 *
 * This project is licensed under the MIT license.
 * Copyright (c) 2018-2019 UnexomWid (https://uw.exom.dev)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef X10_INSTRUCTIONS_H
#define X10_INSTRUCTIONS_H

#include "instruction.h"
#include <unordered_map>

extern std::unordered_map<char, instruction> instruction_list;

extern void initialize_instructions();
bool find_instruction(char id, instruction &instr);
uint8_t parse_num(POINTER_INFO);
bool parse_expression(POINTER_INFO);

void VALUE_INCREMENT(POINTER_INFO);
void VALUE_DECREMENT(POINTER_INFO);
void VALUE_OPERATION(POINTER_INFO);

void INDEX_INCREMENT(POINTER_INFO);
void INDEX_DECREMENT(POINTER_INFO);

void UNCERTAINTY_START(POINTER_INFO);
void UNCERTAINTY_END(POINTER_INFO);

void LOOP_START(POINTER_INFO);
void LOOP_END(POINTER_INFO);

void OUTPUT_WRITE(POINTER_INFO);

void INPUT_READ(POINTER_INFO);
void INPUT_ADD(POINTER_INFO);
void INPUT_XOR(POINTER_INFO);
void INPUT_AND(POINTER_INFO);
void INPUT_OR(POINTER_INFO);

void FILE_OPEN(POINTER_INFO);
void FILE_CLOSE(POINTER_INFO);

extern instruction INSTRUCTION_VALUE_INCREMENT; // Increment char value at current index.
extern instruction INSTRUCTION_VALUE_DECREMENT; // Decrement char value at current index.
extern instruction INSTRUCTION_VALUE_OPERATION; // Execute an operation on value at current index.

extern instruction INSTRUCTION_INDEX_INCREMENT; // Increment index.
extern instruction INSTRUCTION_INDEX_DECREMENT; // Decrement index.

extern instruction INSTRUCTION_UNCERTAINTY_START; // Start an uncertainty;
extern instruction INSTRUCTION_UNCERTAINTY_END; // End an uncertainty;

extern instruction INSTRUCTION_LOOP_START; // Start a loop;
extern instruction INSTRUCTION_LOOP_END; // End a loop;

extern instruction INSTRUCTION_OUTPUT_WRITE; // Write to OUTPUT value from current index.

extern instruction INSTRUCTION_INPUT_READ; // Read from input to value from current index.
extern instruction INSTRUCTION_INPUT_ADD; // Add from input to value from current index.
extern instruction INSTRUCTION_INPUT_XOR; // XOR input with value from current index.
extern instruction INSTRUCTION_INPUT_AND; // AND input with value from current index.
extern instruction INSTRUCTION_INPUT_OR; // OR input with value from current index.

extern instruction INSTRUCTION_FILE_OPEN; // Redirect input or output to file.
extern instruction INSTRUCTION_FILE_CLOSE; // Stop redirecting input or output to file.

#endif