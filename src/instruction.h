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

/// Represents an instruction.
class Instruction
{
	private:
        /// The body of the instruction.
		Body body;

	public:
        /// The identifier of the instruction.
		char identifier;

        /**
         * Initializes a new instance of the Instruction class.
         */
		Instruction();
		/**
		 * Initializes a new instance of the Instruction class.
		 *
		 * @param id The ID of the instruction.
		 * @param bdy The body of the instruction.
		 */
		Instruction(char id, Body bdy);

		/**
		 * Gets the indentifier of the instruction.
		 *
		 * @return The identifier of the instruction.
		 */
		char getIdentifier();
		/**
		 * Sets the identifier of the instruction to a value.
		 *
		 * @param id The value to set the identifier of the instruction to.
		 */
		void setIdentifier(char id);

        /**
         * Gets the body of the instruction.
         *
         * @return The body of the instruction.
         */
		Body getBody();
        /**
         * Sets the body of the instruction to a value.
         *
         * @param id The value to set the body of the instruction to.
         */
		void setBody(Body bdy);

		/**
		 * Executes the instruction.
		 *
		 * @param pointer The data pointer.
		 * @param index The instruction index.
		 * @param script The input script.
         * @param input The default stream from which to receive input.
         * @param output The default stream where to output.
		 * @param file_input The stream from which to receive input.
		 * @param file_output The stream where to output.
		 * @param loop_stack The loop stack.
		 * @param uncertainty_count The amount of open uncertainties.
		 */
		void execute(POINTER_INFO);

		bool operator<(char right);
		bool operator==(char right);
		bool operator>(char right);

		bool operator<(Instruction right);
		bool operator==(Instruction right);
		bool operator>(Instruction right);
};

#endif