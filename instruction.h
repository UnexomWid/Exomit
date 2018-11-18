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
