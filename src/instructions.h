/*
 * Exomit Interpreter - A cross-platform interpreter for Exomit written in C++.
 * Copyright (C) 2018-2019  UnexomWid

 * instructions.h - Contains the declarations of the instruction list and all instructions.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "instruction.h"

#include <vector>

extern std::vector<instruction> instruction_list;

extern void initialize_instructions();
bool find_instruction(char id, instruction &instr);

void VALUE_INCREMENT(POINTER_INFO);
void VALUE_DECREMENT(POINTER_INFO);
void VALUE_OPERATION(POINTER_INFO);

void INDEX_INCREMENT(POINTER_INFO);
void INDEX_DECREMENT(POINTER_INFO);

void LOOP_START(POINTER_INFO);
void LOOP_END(POINTER_INFO);

void STDOUT_WRITE(POINTER_INFO);

void STDIN_READ(POINTER_INFO);
void STDIN_ADD(POINTER_INFO);
void STDIN_XOR(POINTER_INFO);
void STDIN_AND(POINTER_INFO);
void STDIN_OR(POINTER_INFO);

extern instruction INSTRUCTION_VALUE_INCREMENT; // Increment char value at current index.
extern instruction INSTRUCTION_VALUE_DECREMENT; // Decrement char value at current index.
extern instruction INSTRUCTION_VALUE_OPERATION; // Execute an operation on value at current index.

extern instruction INSTRUCTION_INDEX_INCREMENT; // Increment index.
extern instruction INSTRUCTION_INDEX_DECREMENT; // Decrement index.

extern instruction INSTRUCTION_LOOP_START; // Start a loop;
extern instruction INSTRUCTION_LOOP_END; // End a loop;

extern instruction INSTRUCTION_STDOUT_WRITE; // Write to STDOUT value from current index.

extern instruction INSTRUCTION_STDIN_READ; // Read from STDIN to value from current index.
extern instruction INSTRUCTION_STDIN_ADD; // Add from STDIN to value from current index.
extern instruction INSTRUCTION_STDIN_XOR; // XOR STDIN with value from current index.
extern instruction INSTRUCTION_STDIN_AND; // AND STDIN with value from current index.
extern instruction INSTRUCTION_STDIN_OR; // OR STDIN with value from current index.
