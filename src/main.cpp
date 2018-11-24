/*
 * Exomit Interpreter - A cross-platform interpreter for Exomit written in C++.
 * Copyright (C) 2018  UnexomWid

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

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

void error(const char *text);
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
		char current_char;

		if(argc <= 0)
			pointer.push_back(0);
		else
		{
			for(int u = 0; u < argc; u++)
				pointer.push_back(atoi(argv[u]));
		}
		while (script.get(current_char))
		{
			// New line, space and tab.
			if (current_char == 10 || current_char == 13 || current_char == 32 || current_char == 9 || current_char == 11)
				continue;

			instruction i;
			if (find_instruction(current_char, i))
				i.execute(pointer, index, script);
			else 
			{
				printf("%c", current_char); throw std::runtime_error("Invalid instruction");
			}
		}
		std::cout << "\n[INFO] Execution took " << getf_exec_time_ns(chronometer) << "\n";
	}
	catch (std::exception &e)
	{
		std::string err = "[ERROR] [Instruction ";
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