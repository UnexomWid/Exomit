/*
 * Exomit Interpreter - A cross-platform interpreter for Exomit written in C++.
 * Copyright (C) 2018-2019  UnexomWid

 * instructions.cpp - Contains the definitions of the instruction list and all instructions.

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
#include <string>

std::vector<instruction> instruction_list;

instruction INSTRUCTION_VALUE_INCREMENT('+', VALUE_INCREMENT);
instruction INSTRUCTION_VALUE_DECREMENT('-', VALUE_DECREMENT);
instruction INSTRUCTION_VALUE_OPERATION('(', VALUE_OPERATION);

instruction INSTRUCTION_INDEX_INCREMENT('>', INDEX_INCREMENT);
instruction INSTRUCTION_INDEX_DECREMENT('<', INDEX_DECREMENT);

instruction INSTRUCTION_LOOP_START('{', LOOP_START);
instruction INSTRUCTION_LOOP_END('}', LOOP_END);

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

	instruction_list.push_back(INSTRUCTION_LOOP_START);
	instruction_list.push_back(INSTRUCTION_LOOP_END);

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

	if (res >= instruction_list.end())
		return false;

	instr = *(res);
	return true;
}

char parse_num(POINTER_INFO)
{
	if (script.peek() == ']')
		return 0;
	bool neg = false; // Negative number.
	bool val = false; // Value at index.
	bool ind = false; // At index.
	bool add = false; // Add to index.
	bool sub = false; // Subtract from index.

	char op = script.get();

	if (op == '-')
	{
		neg = true;
		op = script.get();
	}

	if (op == '$')
	{
		val = true;
		op = script.get();
	}

	if (op == 'i')
	{
		ind = true;
		op = script.get();
	}

	if (op == '+')
	{
		add = true;
		op = script.get();
	}
	else if (op == '-')
	{
		sub = true;
		op = script.get();
	}

	if (!isdigit(op))
	{
		if (op == ']')
		{
			if (!ind || add || sub)
				throw std::runtime_error("Expected number");
			if (val)
			{
				return neg ? (-1) * pointer.at(index) : pointer.at(index);
			}
			else
			{
				return neg ? (-1) * index : index;
			}
		}
		else if (op == '[')
		{
			if (ind)
			{
				if (val)
				{
					if (add)
						return neg ? (-1) * pointer.at(index + parse_num(POINTER_INFO_PARAMS)) : pointer.at(index + parse_num(POINTER_INFO_PARAMS));
					if (sub)
						return neg ? (-1) * pointer.at(index - parse_num(POINTER_INFO_PARAMS)) : pointer.at(index - parse_num(POINTER_INFO_PARAMS));
					return neg ? (-1) * pointer.at(parse_num(POINTER_INFO_PARAMS)) : pointer.at(parse_num(POINTER_INFO_PARAMS));
				}
				else
				{
					if (add)
						return neg ? (-1) * (index + parse_num(POINTER_INFO_PARAMS)) : index + parse_num(POINTER_INFO_PARAMS);
					if (sub)
						return neg ? (-1) * (index - parse_num(POINTER_INFO_PARAMS)) : index - parse_num(POINTER_INFO_PARAMS);
					return neg ? (-1) * parse_num(POINTER_INFO_PARAMS) : parse_num(POINTER_INFO_PARAMS);
				}
			}
			else
			{
				return neg ? (-1) * parse_num(POINTER_INFO_PARAMS) : parse_num(POINTER_INFO_PARAMS);
			}
		}
	}
	else
	{

		std::string res;
		res.push_back(op);

		while (isdigit(op = script.get()))
		{
			res.push_back(op);
		}

		if(op != ']')
			throw std::runtime_error("Expected ending square bracket");
		while (script.peek() == ']')
			script.ignore(1);

		int num = stoi(res);

		if (ind)
		{
			if (val)
			{
				if (add)
					return neg ? (-1) * pointer.at(index + num) : pointer.at(index + num);
				if (sub)
					return neg ? (-1) * pointer.at(index - num) : pointer.at(index - num);
				return neg ? (-1) * pointer.at(num) : pointer.at(num);
			}
			else
			{
				if (add)
					return neg ? (-1) * (index + parse_num(POINTER_INFO_PARAMS)) : index + num;
				if (sub)
					return neg ? (-1) * (index - num) : index - num;
				return neg ? (-1) * num : num;
			}
		}
		else
		{
			return neg ? (-1) * num : num;
		}
	}
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
	if (script.peek() != '[') // Apply to current index.
	{
		script.get(op);
		if (script.get() != '[') // Square bracket.
			throw std::runtime_error("Expected square bracket");

		switch (op)
		{
			case '$':
			{
				pointer.at(index) = parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '+':
			{
				pointer.at(index) += parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '-':
			{
				pointer.at(index) -= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '*':
			{
				pointer.at(index) *= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '/':
			{
				pointer.at(index) /= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case 'x':
			{
				pointer.at(index) ^= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '&':
			{
				pointer.at(index) &= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '|':
			{
				pointer.at(index) |= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			default:
			{
				throw std::runtime_error("Invalid operator");
				break;
			}
		}
	}
	else
	{
		int new_index = parse_num(POINTER_INFO_PARAMS); // New index.
		while (pointer.size() <= new_index) // Prevents 'invalid vector<t> subscript'.
			pointer.push_back(0); // Pad with 0s until the new index is reached.

		script.get(op);
		if (script.get() != '[') // Square bracket.
			throw std::runtime_error("Expected square bracket");

		switch (op)
		{
			case '$':
			{
				pointer.at(new_index) = parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '+':
			{
				pointer.at(new_index) += parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '-':
			{
				pointer.at(new_index) -= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '*':
			{
				pointer.at(new_index) *= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '/':
			{
				pointer.at(new_index) /= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case 'x':
			{
				pointer.at(new_index) ^= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '&':
			{
				pointer.at(new_index) &= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			case '|':
			{
				pointer.at(new_index) |= parse_num(POINTER_INFO_PARAMS);
				break;
			}
			default:
			{
				throw std::runtime_error("Invalid operator");
				break;
			}
		}
	}

	script.ignore(1); // Ending round bracket.
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

void LOOP_START(POINTER_INFO)
{
	if (script.get() != '[') // Square bracket.
		throw std::runtime_error("Expected square bracket");

	loop_stack.push(script.tellg()); // Add the position to the stack.

	if (parse_num(POINTER_INFO_PARAMS) == 0) // Skip loop.
	{
		loop_stack.pop(); // Remove the position from the stack.
		int open_count = 1;
		while (open_count > 0)
		{
			char c = script.get();
			if (c == '{')
				open_count++;
			else if (c == '}')
				open_count--;
		}
	}
}

void LOOP_END(POINTER_INFO)
{
	int after_loop = script.tellg();

	script.seekg(loop_stack.top());

	if (parse_num(POINTER_INFO_PARAMS) == 0) // Skip loop.
	{
		loop_stack.pop(); // Remove the position from the stack.
		script.seekg(after_loop);
	}
}

void STDOUT_WRITE(POINTER_INFO)
{
	char format = script.peek();

	if (format != 'n' && format != 'c' && format != '_' && format != '\\')
	{
		printf("%c", pointer.at(index));
		return;
	}

	while ((format == 'n' || format == 'c' || format == '_' || format == '\\') && !script.eof())
	{
		script.ignore(1);

		if (format == 'n')
		{
			printf("%d", pointer.at(index));
		}
		else if (format == 'c')
		{
			printf("%c", pointer.at(index));
		}
		else if (format == '_')
		{
			printf(" ");
		}
		else if (format == '\\')
		{
			printf("\n");
		}

		format = script.peek();
	}
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