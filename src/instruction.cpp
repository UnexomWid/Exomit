/*
 * X10 Interpreter - A cross-platform interpreter for X10 written in C++.
 * Copyright (C) 2018-2019  UnexomWid

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