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

#include "instruction_handler.h"
#include "timerh/timer.h"

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <iostream>

/**
 * Writes an error to STDERR and terminates the program with the status code 1.
 *
 * @param[in] text The error to write.
 */
void error(const char *text);
/**
 * Returns a string from a specified format.
 *
 * @param count The maximum amount of characters of the string.
 * @param format The format to create the string from.
 * @param ... The additional arguments for the string format.
 *
 * @return A string from the specified format.
 */
std::string formatString(uint16_t count, const char *format, ...);
/**
 * Opens a file, opens an input stream from that file, and returns the value of success.
 *
 * @param file The file to open.
 * @param script The variable which will contain the input stream which was opened from the file.
 *
 * @return True, if the file was opened successfully. False otherwise.
 */
bool openFile(const char* file, std::ifstream &script);
/**
 * Closes a file input stream and a file output stream.
 *
 * @param file_input The file input stream to close.
 * @param file_output The file output stream to close.
 */
void closeFiles(std::ifstream *&file_input, std::ofstream *&file_output);
/**
 * Interprets a script.
 *
 * @param script The script to interpret, as a file input stream.
 * @param input The stream from which to receive input.
 * @param output The stream where to output.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 */
void interpret(std::ifstream &script, std::istream &input, std::ostream &output, uint32_t argc, char *argv[]);

/**
 * The main function.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 *
 * @return The program exit code.
 */
int main(int argc, char *argv[]) {
	if (argc < 2)
		error("[ERROR]: Invalid arguments");

	const char *scriptFile = *(argv + 1);

	std::ifstream script;

	if (!openFile(scriptFile, script))
		error("[ERROR]: Invalid script file");

	// Ignore the name and script file.
	argc -= 2;
	argv += 2;

	// Initialize instruction list.
    initializeInstructions();
	interpret(script, std::cin, std::cout, argc, argv);
	script.close();

	exit(EXIT_SUCCESS);
}

void interpret(std::ifstream &script, std::istream &input, std::ostream &output, uint32_t argc, char *argv[]) {
    CHRONOMETER chronometer = time_now();

    std::ifstream *file_input = nullptr;
    std::ofstream *file_output = nullptr;

	try {
		// Pointer info.
        char current_char;
        uint32_t index = 0;
		std::vector<uint8_t> pointer;
        uint32_t uncertainty_count = 0;
		std::stack<std::streampos> loop_stack;

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
				else throw std::runtime_error(formatString(19u + strlen(argv[0]), "%s '%s'", "Invalid argument", argv[0]));
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

			Instruction i;
			if (findInstruction(current_char, i))
				i.execute(POINTER_INFO_PARAMS);
			else throw std::runtime_error(formatString(23, "%s '%c'", "Invalid instruction", current_char));
		}

        std::string time = getf_exec_time_ns(chronometer);
		output << formatString(24 + time.size(), "\n%s %s\n", "[INFO] Execution took", time.c_str());
	}
	catch (std::exception &e) {
	    if(script.tellg() == -1) {
	        script.clear();
            script.seekg(0, std::ios::end);
        }
		std::string err = "\n[ERROR] [Instruction ";
		err.append(std::to_string(script.tellg()));
		err.append("]: ");
		err.append(e.what());
		error(err.c_str());
	}

    closeFiles(file_input, file_output);
}

void error(const char *text) {
	std::cerr << text;
	exit(EXIT_FAILURE);
}

std::string formatString(uint16_t count, const char *format, ...) {
	va_list argp;
	va_start(argp, format);

	char *buffer = (char*)malloc(count);
	vsprintf(buffer, format, argp);

	return std::string(buffer);
}

bool openFile(const char* file, std::ifstream &script) {
	try {
		script.open(file, std::ios::binary);
		return !script.fail();
	}
	catch(std::exception &e){
		return false;
	}
}

void closeFiles(std::ifstream *&file_input, std::ofstream *&file_output) {
    if(file_input != nullptr) {
        file_input -> close();
        delete file_input;
        file_input = nullptr;
    }
    if(file_output != nullptr) {
        file_output -> close();
        delete file_output;
        file_output = nullptr;
    }
}