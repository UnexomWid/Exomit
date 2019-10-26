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

#ifndef X10_INSTRUCTION_H
#define X10_INSTRUCTION_H

#include "definitions.h"

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

#endif