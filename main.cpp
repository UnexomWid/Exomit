#include "instructions.h"

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

void error(const char *text);
bool fileExists(const char* file);
void interpret(std::ifstream &script, int argc, char *argv[]);

int main(int argc, char *argv[])
{
	if (argc < 2)
		error("[Error]: Invalid arguments");

	const char *scriptFile = *(argv + 1);

	if (!fileExists(scriptFile))
		error("[Error]: Invalid script file");

	std::ifstream script;
	script.open(scriptFile);

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
			else throw std::runtime_error("Invalid instruction");
		}
	}
	catch (std::exception &e)
	{
		std::string err = "[Error] [Instruction ";
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

bool fileExists(const char* file)
{
	struct stat buffer;
	return (stat(file, &buffer) == 0);
}