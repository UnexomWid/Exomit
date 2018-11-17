/*
 * EXCS Interpreter - A cross-platform interpreter for Exom CrypticScript written in C++.
 * Copyright (C) 2018 UnexomWid
 
 * instructions.cpp - Contains the definitions of all instructions, the instruction list and functions used to interact with it.

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
 
 
 
#include "instructions.h"
#include <algorithm>

std::vector<instruction> instruction_list;

instruction INSTRUCTION_VALUE_INCREMENT('+', VALUE_INCREMENT);
instruction INSTRUCTION_VALUE_DECREMENT('-', VALUE_DECREMENT);
instruction INSTRUCTION_VALUE_OPERATION('(', VALUE_OPERATION);

instruction INSTRUCTION_INDEX_INCREMENT('>', INDEX_INCREMENT);
instruction INSTRUCTION_INDEX_DECREMENT('<', INDEX_DECREMENT);

instruction INSTRUCTION_STDOUT_WRITE('^', STDOUT_WRITE);

instruction INSTRUCTION_STDIN_READ('V', STDIN_READ);
instruction INSTRUCTION_STDIN_ADD('v', STDIN_ADD);
instruction INSTRUCTION_STDIN_XOR('x', STDIN_XOR);
instruction INSTRUCTION_STDIN_AND('&', STDIN_AND);
instruction INSTRUCTION_STDIN_OR('|', STDIN_OR);

void initialize_instructions()
{
	instruction_list.push_back(INSTRUCTION_VALUE_INCREMENT);
	instruction_list.push_back(INSTRUCTION_VALUE_DECREMENT);
	instruction_list.push_back(INSTRUCTION_VALUE_OPERATION);

	instruction_list.push_back(INSTRUCTION_INDEX_INCREMENT);
	instruction_list.push_back(INSTRUCTION_INDEX_DECREMENT);

	instruction_list.push_back(INSTRUCTION_STDOUT_WRITE);

	instruction_list.push_back(INSTRUCTION_STDIN_READ);
	instruction_list.push_back(INSTRUCTION_STDIN_ADD);
	instruction_list.push_back(INSTRUCTION_STDIN_XOR);
	instruction_list.push_back(INSTRUCTION_STDIN_AND);
	instruction_list.push_back(INSTRUCTION_STDIN_OR);

	std::sort(instruction_list.begin(), instruction_list.end(), [](instruction a, instruction b) { return a < b; });
}

bool find_instruction(char id, instruction &instr)
{
	std::vector<instruction>::iterator res;
	res = std::lower_bound(instruction_list.begin(), instruction_list.end(), id);

	if (*res > id)
		return false;

	instr = *(res);
	return true;
}

void VALUE_INCREMENT(POINTER_INFO)
{
	pointer.at(index)++;
}

void VALUE_DECREMENT(POINTER_INFO)
{
	pointer.at(index)--;
}

void VALUE_OPERATION(POINTER_INFO)
{
	char op = 0;
	script.get(op);

	switch (op)
	{
		case '$':
		{
			char num[255];
			script.getline(num, 255, ')');

			pointer.at(index) = atoi(num);
			break;
		}
		case '+':
		{
			char num[255];
			script.getline(num, 255, ')');

			pointer.at(index) += atoi(num);
			break;
		}
		case '-':
		{
			char num[255];
			script.getline(num, 255, ')');

			pointer.at(index) -= atoi(num);
			break;
		}
		case '*':
		{
			char num[255];
			script.getline(num, 255, ')');

			pointer.at(index) *= atoi(num);
			break;
		}
		case '/':
		{
			char num[255];
			script.getline(num, 255, ')');

			pointer.at(index) /= atoi(num);
			break;
		}
		case 'x':
		{
			char num[255];
			script.getline(num, 255, ')');

			pointer.at(index) ^= atoi(num);
			break;
		}
		case '&':
		{
			char num[255];
			script.getline(num, 255, ')');

			pointer.at(index) &= atoi(num);
			break;
		}
		case '|':
		{
			char num[255];
			script.getline(num, 255, ')');

			pointer.at(index) |= atoi(num);
			break;
		}
		default:
		{
			throw std::runtime_error("Invalid operator");
			break;
		}
	}
}

void INDEX_INCREMENT(POINTER_INFO)
{
	index++;
	if (index > pointer.size() - 1)
		pointer.push_back(0);
}

void INDEX_DECREMENT(POINTER_INFO)
{
	index--;
}

void STDOUT_WRITE(POINTER_INFO)
{
	printf("%c", pointer.at(index));
}

void STDIN_READ(POINTER_INFO)
{
	int input = 0;
	scanf("%d", &input);
	pointer.at(index) = input;
}

void STDIN_ADD(POINTER_INFO)
{
	int input = 0;
	scanf("%d", &input);
	pointer.at(index) += input;
}

void STDIN_XOR(POINTER_INFO)
{
	int input = 0;
	scanf("%d", &input);
	pointer.at(index) ^= input;
}

void STDIN_AND(POINTER_INFO)
{
	int input = 0;
	scanf("%d", &input);
	pointer.at(index) &= input;
}

void STDIN_OR(POINTER_INFO)
{
	int input = 0;
	scanf("%d", &input);
	pointer.at(index) |= input;
}