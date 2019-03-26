/*
 * Exomit Interpreter - A cross-platform interpreter for Exomit written in C++.
 * Copyright (C) 2018-2019  UnexomWid

 * main.cpp - Contains the entry point of the application.

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
#include "timerh/timer.h"

#include <stdarg.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

void error(const char *text);
std::string format_string(int count, const char *format, ...);
bool fileExists(const char* file, std::ifstream &script);
void interpret(std::ifstream &script, int argc, char *argv[]);

CHRONOMETER chronometer;

int main(int argc, char *argv[])
{
	if (argc < 2)
		error("[ERROR]: Invalid arguments");

	const char *scriptFile = *(argv + 1);

	std::ifstream script;

	if (!fileExists(scriptFile, script))
		error("[ERROR]: Invalid script file");

	// Executable name and script file not needed.
	argc -= 2;
	argv += 2;

	// Initialize instruction list.
	initialize_instructions();
	interpret(script, argc, argv);
	script.close();

	exit(EXIT_SUCCESS);
}

void interpret(std::ifstream &script, int argc, char *argv[])
{
	try
	{
		chronometer = time_now();

		int index = 0;
		std::vector<char> pointer;
		std::stack<std::streampos> loop_stack;
		char current_char;

		try
		{

			if (argc < 1)
				pointer.push_back(0);
			else
			{
				// As numbers.
				if (strcmp(argv[0], "-n") == 0 || strcmp(argv[0], "-N") == 0)
				{
					argc--;
					argv++;

					pointer.push_back(argc);

					for (int u = 0; u < argc; u++)
						pointer.push_back(atoi(argv[u]));
				}
				// As characters.
				else if (strcmp(argv[0], "-c") == 0 || strcmp(argv[0], "-C") == 0)
				{
					argc--;
					argv++;

					pointer.push_back(argc);

					for (int u = 0; u < argc; u++)
						pointer.push_back(*argv[u]);
				}
				// As a string.
				else if (strcmp(argv[0], "-s") == 0 || strcmp(argv[0], "-S") == 0)
				{
					argc--;
					argv++;

					std::string buffer;
					for (int u = 0; u < argc; u++)
						buffer.append(argv[u]);

					pointer.push_back(buffer.length());

					for (int u = 0; u < buffer.length(); u++)
						pointer.push_back(buffer.at(u));
				}
				else throw std::runtime_error(format_string(19 + strlen(argv[0]), "%s '%s'", "Invalid argument", argv[0]));
			}
		}
		catch (std::exception &e)
		{
			std::string err = "\n[ERROR]: ";
			err.append(e.what());
			error(err.c_str());
		}

		while (script.get(current_char))
		{
			// New line, space and tab.
			if (current_char == 10 || current_char == 13 || current_char == 32 || current_char == 9 || current_char == 11)
				continue;

			instruction i;
			if (find_instruction(current_char, i))
				i.execute(POINTER_INFO_PARAMS);
			else throw std::runtime_error(format_string(23, "%s '%c'", "Invalid instruction", current_char));
		}
		printf("\n%s %s\n", "[INFO] Execution took ", getf_exec_time_ns(chronometer).c_str());
	}
	catch (std::exception &e)
	{
		std::string err = "\n[ERROR] [Instruction ";
		err.append(std::to_string(script.tellg()));
		err.append("]: ");
		err.append(e.what());
		error(err.c_str());
	}
}

void error(const char *text)
{
	std::fprintf(stderr, text);
	exit(EXIT_FAILURE);
}

std::string format_string(int count, const char *format, ...)
{
	va_list argp;
	va_start(argp, format);

	char *buffer = (char*)malloc(count);
	vsprintf(buffer, format, argp);

	return std::string(buffer);
}

bool fileExists(const char* file, std::ifstream &script)
{
	try
	{
		script.open(file);
		return !script.fail();
	}
	catch(std::exception &e)
	{
		return false;
	}
}