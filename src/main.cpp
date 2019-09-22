/*
 * Exomit Interpreter - A cross-platform interpreter for Exomit written in C++.
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

#include "instruction_handler.h"
#include "timerh/timer.h"

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <iostream>

void error(const char *text);
std::string format_string(uint16_t count, const char *format, ...);
bool open_file(const char* file, std::ifstream &script);
void interpret(std::ifstream &script, std::istream &input, std::ostream &output, uint32_t argc, char *argv[]);

int main(int argc, char *argv[]) {
	if (argc < 2)
		error("[ERROR]: Invalid arguments");

	const char *scriptFile = *(argv + 1);

	std::ifstream script;

	if (!open_file(scriptFile, script))
		error("[ERROR]: Invalid script file");

	// Ignore the name and script file.
	argc -= 2;
	argv += 2;

	// Initialize instruction list.
	initialize_instructions();
	interpret(script, std::cin, std::cout, argc, argv);
	script.close();

	exit(EXIT_SUCCESS);
}

void interpret(std::ifstream &script, std::istream &input, std::ostream &output, uint32_t argc, char *argv[]) {
	try {
		CHRONOMETER chronometer = time_now();

		// Pointer info.
        uint32_t index = 0;
		std::vector<uint8_t> pointer;
		std::stack<std::streampos> loop_stack;
        uint32_t uncertainty_count = 0;
		char current_char;

		try {
			if (argc < 1) {
                pointer.push_back(0);
            }
			else {
				// As numbers.
				if (strcmp(argv[0], "-n") == 0 || strcmp(argv[0], "-N") == 0) {
					argc--;
					argv++;

					pointer.push_back(argc);

					for (uint32_t i = 0; i < argc; ++i)
						pointer.push_back(atoi(argv[i]));
				}
				// As characters.
				else if (strcmp(argv[0], "-c") == 0 || strcmp(argv[0], "-C") == 0) {
					argc--;
					argv++;

					pointer.push_back(argc);

					for (uint32_t i = 0; i < argc; ++i)
						pointer.push_back(*argv[i]);
				}
				// As a string.
				else if (strcmp(argv[0], "-s") == 0 || strcmp(argv[0], "-S") == 0) {
					argc--;
					argv++;

					std::string buffer;
					for (uint32_t i = 0; i < argc; ++i)
						buffer.append(argv[i]);

					pointer.push_back(buffer.length());

					for (char c : buffer)
						pointer.push_back(c);
				}
				else throw std::runtime_error(format_string(19u + strlen(argv[0]), "%s '%s'", "Invalid argument", argv[0]));
			}
		}
		catch (std::exception &e) {
			std::string err = "\n[ERROR]: ";
			err.append(e.what());
			error(err.c_str());
		}

		while (script.get(current_char)) {
			// New line, space and tab.
			if (current_char == 10 || current_char == 13 || current_char == 32 || current_char == 9 || current_char == 11)
				continue;

			instruction i;
			if (find_instruction(current_char, i))
				i.execute(POINTER_INFO_PARAMS);
			else throw std::runtime_error(format_string(23, "%s '%c'", "Invalid instruction", current_char));
		}

        std::string time = getf_exec_time_ns(chronometer);
		output << format_string(22 + time.size(), "\n%s %s\n", "[INFO] Execution took ", time.c_str());
	}
	catch (std::exception &e) {
		std::string err = "\n[ERROR] [Instruction ";
		err.append(std::to_string(script.tellg()));
		err.append("]: ");
		err.append(e.what());
		error(err.c_str());
	}
}

void error(const char *text) {
	std::cerr << text;
	exit(EXIT_FAILURE);
}

std::string format_string(uint16_t count, const char *format, ...) {
	va_list argp;
	va_start(argp, format);

	char *buffer = (char*)malloc(count);
	vsprintf(buffer, format, argp);

	return std::string(buffer);
}

bool open_file(const char* file, std::ifstream &script) {
	try {
		script.open(file, std::ios::binary);
		return !script.fail();
	}
	catch(std::exception &e){
		return false;
	}
}