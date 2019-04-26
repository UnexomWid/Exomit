/*
 * Exomit Interpreter - A cross-platform interpreter for Exomit written in C++.
 * Copyright (C) 2018-2019  UnexomWid

 * definitions.h - Contains global definitions.

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

#include <vector>
#include <fstream>
#include <stack>

#define POINTER_INFO std::vector<unsigned char> &pointer, int &index, std::ifstream &script, std::stack<std::streampos> &loop_stack, int &uncertainty_count
#define POINTER_INFO_PARAMS pointer, index, script, loop_stack, uncertainty_count

#define NUMBER_START '['
#define NUMBER_END ']'
#define NUMBER_MODIFIER_INDEX 'i'
#define NUMBER_MODIFIER_VALUE_AT '$'
#define NUMBER_MODIFIER_NEGATIVE '-'

#define RELATIONAL_EQUAL "EQ"
#define RELATIONAL_NOT_EQUAL "NEQ"
#define RELATIONAL_GREATER_THAN "GT"
#define RELATIONAL_GREATER_THAN_OR_EQUAL "GTE"
#define RELATIONAL_LESS_THAN "LT"
#define RELATIONAL_LESS_THAN_OR_EQUAL "LTE"

#define LOGICAL_AND "AND"
#define LOGICAL_OR "OR"
#define LOGICAL_XOR "XOR"

typedef void(*instruction_body)(POINTER_INFO);
