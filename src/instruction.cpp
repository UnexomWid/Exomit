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

#include "instruction.h"

instruction::instruction() {
    identifier = '\0';
    body = nullptr;
}

instruction::instruction(char id, instruction_body bdy) {
	identifier = id;
	body = bdy;
}

char instruction::getIdentifier() {
	return identifier;
}

void instruction::setIdentifier(char id) {
	identifier = id;
}

instruction_body instruction::getBody() {
	return body;
}

void instruction::setBody(instruction_body bdy) {
	body = bdy;
}

void instruction::execute(POINTER_INFO) {
	body(POINTER_INFO_PARAMS);
}

bool instruction::operator<(char right) {
	return identifier < right;
}

bool instruction::operator==(char right) {
	return identifier == right;
}

bool instruction::operator>(char right) {
	return identifier > right;
}

bool instruction::operator<(instruction right) {
	return identifier < right.identifier;
}

bool instruction::operator==(instruction right) {
	return identifier == right.identifier;
}

bool instruction::operator>(instruction right) {
	return identifier > right.identifier;
}