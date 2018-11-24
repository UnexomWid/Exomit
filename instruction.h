/*
 * Exomit Interpreter - A cross-platform interpreter for Exomit written in C++.
 * Copyright (C) 2018  UnexomWid

 * instruction.h - Contains the declaration of the instruction class.

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

#define POINTER_INFO std::vector<char> &pointer, int &index, std::ifstream &script
typedef void(*instruction_body)(POINTER_INFO);

class instruction
{
	private:
		instruction_body body;

	public:
		char identifier;

		instruction();
		instruction(char id, instruction_body bdy);

		char getIdentifier();
		void setIdentifier(char id);

		instruction_body getBody();	
		void setBody(instruction_body bdy);

		void execute(POINTER_INFO);

		bool operator<(char right);
		bool operator==(char right);
		bool operator>(char right);

		bool operator<(instruction right);
		bool operator==(instruction right);
		bool operator>(instruction right);
};
