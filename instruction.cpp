#include "instruction.h"

instruction::instruction()
{
	
}

instruction::instruction(char id, instruction_body bdy)
{
	identifier = id;
	body = bdy;
}

char instruction::getIdentifier()
{
	return identifier;
}

void instruction::setIdentifier(char id)
{
	identifier = id;
}

instruction_body instruction::getBody()
{
	return body;
}

void instruction::setBody(instruction_body bdy)
{
	body = bdy;
}

void instruction::execute(POINTER_INFO)
{
	body(pointer, index, script);
}

bool instruction::operator<(char right)
{
	return identifier < right;
}

bool instruction::operator==(char right)
{
	return identifier == right;
}

bool instruction::operator>(char right)
{
	return identifier > right;
}

bool instruction::operator<(instruction right)
{
	return identifier < right.identifier;
}

bool instruction::operator==(instruction right)
{
	return identifier == right.identifier;
}

bool instruction::operator>(instruction right)
{
	return identifier > right.identifier;
}