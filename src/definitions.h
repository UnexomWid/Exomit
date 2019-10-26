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

#ifndef TMP_DEFINITIONS_H
#define TMP_DEFINITIONS_H

#include <stack>
#include <vector>
#include <fstream>
#include <istream>
#include <ostream>

#define POINTER_INFO std::vector<uint8_t> &pointer, uint32_t &index, std::ifstream &script, std::istream &input, std::ostream &output, std::ifstream *&file_input, std::ofstream *&file_output, std::stack<std::streampos> &loop_stack, uint32_t &uncertainty_count
#define POINTER_INFO_PARAMS pointer, index, script, input, output, file_input, file_output, loop_stack, uncertainty_count

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

#define CONDITIONAL_AND "AND"
#define CONDITIONAL_OR "OR"
#define CONDITIONAL_XOR "XOR"

typedef void(*instruction_body)(POINTER_INFO);

#endif