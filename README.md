<p align="center">
  <img src="img/logo.png" alt="X10">
</p>

# About <a href="https://cmake.org/cmake/help/v3.0/release/3.0.0.html"><img align="right" src="https://img.shields.io/badge/CMake-3.0-CCCCCD?logo=CMake" alt="CMake 3.0" /></a><a href="https://en.wikipedia.org/wiki/C%2B%2B17"><img align="right" src="https://img.shields.io/badge/C%2B%2B-17-00599C?logo=C%2B%2B" alt="C++ 17" /></a>
**X10** (_eXTENded_) is an esoteric programming language that uses a wide variety of instructions.

This is a cross-platform interpreter for X10 written in C++.

# License <a href="https://github.com/UnexomWid/X10/blob/master/LICENSE"><img align="right" src="https://img.shields.io/badge/License-GPLv3-blue.svg" alt="License: GPL v3" /></a>
The X10 language was created by [UnexomWid](https://uw.exom.dev). It is licensed under the [GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html) license.

# Releases

>Note: versions with the suffix **R** are considered stable releases, while those with the suffix **D** are considered unstable.

[v3.0D](https://github.com/UnexomWid/X10/releases/tag/v3.0D) - September 23, 2019

[v2.1R](https://github.com/UnexomWid/X10/releases/tag/v2.1R) - May 3, 2019

[v2.0R](https://github.com/UnexomWid/X10/releases/tag/v2.0R) - May 1, 2019

[v1.1R](https://github.com/UnexomWid/X10/releases/tag/v1.1R) - March 26, 2019

[v1.0R](https://github.com/UnexomWid/X10/releases/tag/v1.0R) - January 19, 2019

# X10
X10 consists of an instruction pointer (called _index_), a moveable data pointer (called _pointer_) and multiple instructions.

The pointer contains references to bytes (called _values_). Each value represents the ASCII code of a character.

Each instruction has an _identifier_ (represented by a character) and a _body_ (represented by a function).

The body of an instruction can perform actions on the index, the pointer and on the input stream.

## Using the interpreter

The X10 Interpreter accepts command-line arguments.

The first argument *must* be the script file to execute.

Other arguments are optional. These are used to initialize the vector of values.

The optional arguments can be in the form of numbers `-n`, characters `-c` or a single string `-s`.

The value at index 0 will always store the amount of passed arguments. The arguments will be stored at index 1 and forwards.

### Examples

```
x10 test.x10
// Executes the "test.x10" script.
```

```
x10 test.x10 -n 50 1 125 9 74
// Sets the value at index 0 to 5 (because there are 5 arguments)
// Sets the value at index 1 to 50, the value at index 2 to 1 and so on. . .
// Executes the "test.x10" script.
```

```
x10 test.x10 -c a b h U z L
// Sets the value at index 0 to 6 (because there are 6 arguments)
// Sets the value at index 1 to 97 ('a' = 97), the value at index 2 to 98 ('b' = 98) and so on. . .
// Executes the "test.x10" script.
```

```
x10 test.x10 -s H ello
// Sets the value at index 0 to 6 (because there are 6 arguments)
// Sets the value at index 1 to 72 ('H' = 97), the value at index 2 to 32 (' ' = 32) and so on. . .
// (Note that spaces are considered characters too)
// Executes the "test.x10" script.
```

## List of instructions

| Instruction     | Identifier       | Description                                                                                                                                                                                                                                                                                          |
|-----------------|------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| VALUE_INCREMENT | +                | Increments the value at the current index                                                                                                                                                                                                                                                            |
| VALUE_DECREMENT | -                | Decrements the value at the current index                                                                                                                                                                                                                                                            |
| VALUE_OPERATION | ([INDEX]OP[NUM]) | Executes an operation on the value at an index. See below _OP_ and _[NUM]_                                                                                                                                                                                                                           |
| INDEX_INCREMENT | >                | Increments the index                                                                                                                                                                                                                                                                                 |
| INDEX_DECREMENT | <                | Decrements the index                                                                                                                                                                                                                                                                                 |
|UNCERTAINTY_START| ?EXP             | Marks the start of an uncertainty, which is executed if the expression EXP is true                                                                                                                                                                                                                   |
| UNCERTAINTY_END | !                | Marks the end of an uncertainty                                                                                                                                                                                                                                                                      |
| LOOP_START      | {EXP             | Marks the start of a loop, which is executed while the expression EXP is true                                                                                                                                                                                                                        |
| LOOP_END        | }                | Marks the end of a loop                                                                                                                                                                                                                                                                              |
| OUTPUT_WRITE    | ^                | Writes the value at the current index, as a character. Also searches forwards for other characters (without square brackets): [c] prints the current value as a character, [n] prints the current value as a number, [_] prints a space, [\\] prints the `\n` character. See below _Script Examples_ |
| INPUT_READ      | V                | Sets the value at the current index to the input                                                                                                                                                                                                                                                     |
| INPUT_ADD       | v                | Adds the input to the value at the current index                                                                                                                                                                                                                                                     |
| INPUT_XOR       | x                | Sets the value at the current index to XOR(input, value)                                                                                                                                                                                                                                             |
| INPUT_AND       | &                | Sets the value at the current index to AND(input, value)                                                                                                                                                                                                                                             |
| INPUT_OR        | \|                | Sets the value at the current index to OR(input, value)                                                                                                                                                                                                                                              |
| FILE_OPEN       | Fv^"PATH"        | Redirects the input (v) or output (^) to the file located at PATH                                                                                                                                                                                                                                    |
| FILE_CLOSE      | fv^              | Stops redirecting the input (v) or output (^) to the file                                                                                                                                                                                                                                            |

### OP

Represents an operation that executes on a value. It takes [NUM] as an argument.

#### List of operations

| Operation |                    Description                    |
|:---------:|:-------------------------------------------------:|
|     $     |              Sets the value to [NUM]              |
|     +     |              Adds [NUM] to the value              |
|     -     |           Subtracts [NUM] from the value          |
|     *     |           Multiplies the value by [NUM]           |
|     /     |             Divides the value by [NUM]            |
|     %     | Divides the value by [NUM] and gets the remainder |
|     x     | Sets the value to the result of XOR(value, [NUM]) |
|     &     | Sets the value to the result of AND(value, [NUM]) |
|     \|     |  Sets the value to the result of OR(value, [NUM]  |

### [NUM]

Represents a number, in square brackets. A `[NUM]` may include another `[NUM]` (see below).

#### Examples of [NUM]

```
[5] 
// 5
```

```
[-5] 
// -5
```

```
[i] 
// The current index
```

```
[-i] 
// The current index, negated.
```

```
[$i] 
// The value at the current index.
```

```
[-$i] 
// The value at current index, negated.
```


```
[i+5] 
// The current index + 5;
```

```
[-i+5] 
// The current index + 5, negated.
// Note: it may seem like i is negated and then added to 5.
// However, that is not the case. The whole expression (i+5) is negated.
// - negates everyting after it.
```

```
[$i+5] 
// The value at (index+5).
// If (index+5) isn't a valid index, an exception will be thrown.
```

```
[$i5] 
// The value at index 5.
```

```
[-$i5] 
// The value at index 5, negated.
```

```
[$i+[i]] 
// The value at (current_index + current_index).
```

```
[$i+[$i]] 
// The value at (current_index + value_at(current_index)).
```

### Uncertainties and loops

An uncertainty starts with `?EXP` and ends with `!`. Similarly, A loop starts with `{EXP` and ends with `}`.

The uncertainty is executed once, if the expression `EXP` is true (see below _Expressions_).

The loop is executed while the expression `EXP` is true. When the expression becomes false, the loop ends and the execution of the script is resumed from the end of the loop (the `}` character).

>Note: `EXP` is checked at the start of every iteration, including the first one.
>This means the loop will never execute if `EXP` is false to begin with.

#### Syntax

_Uncertainties_: ?`EXP`instructions_go_here!

_Loops_: {`EXP`instructions_go_here}

#### Expression

An expression is made up of 2 numbers and a relational operator:

```
[number_1]RELATIONAL_OPERATOR[number_2]
```

You can also chain expressions with no limit, using the conditional operators (see below _Relational Operators_ and _Conditional Operators_)

```
[number_1]RELATIONAL_OPERATOR[number_2]CONDITIONAL_OPERATOR[number_3]RELATIONAL_OPERATOR[number_4]
```

> Note: chained expressions are evaluated recursively. Here are some examples:
>
> `EXP_1` AND (`EXP_2` AND (`EXP_3` AND ...))
>
> `EXP_1` OR (`EXP_2` OR (`EXP_3` OR ...))
>
> `EXP_1` OR (`EXP_2` AND (`EXP_3` OR ...))
>
> Currently, it's not possible to do something like this:
>
> (`EXP_1` OR `EXP_2`) AND (`EXP_3` OR `EXP_4`)

##### List of Relational Operators

| Relational Operator              | Identifier | Description                                                                 |
|----------------------------------|------------|-----------------------------------------------------------------------------|
| RELATIONAL_EQUAL                 | EQ         | Checks whether the left number is equal to the right number                 |
| RELATIONAL_NOT_EQUAL             | NEQ        | Checks whether the left number is not equal to the right number             |
| RELATIONAL_GREATER_THAN          | GT         | Checks whether the left number is greater than the right number             |
| RELATIONAL_GREATER_THAN_OR_EQUAL | GTE        | Checks whether the left number is greater than or equal to the right number |
| RELATIONAL_LESS_THAN             | LT         | Checks whether the left number is less than the right number                |
| RELATIONAL_LESS_THAN_OR_EQUAL    | LTE        | Checks whether the left number is less than or equal to the right number    |

##### List of Conditional Operators

| Conditional Operator | Identifier | Description                                   |
|----------------------|------------|-----------------------------------------------|
| CONDITIONAL_AND      | AND        | Checks whether both expressions are true      |
| CONDITIONAL_OR       | OR         | Checks whether at lest one expression is true |
| CONDITIONAL_XOR      | XOR        | Checks whether the expressions are not equal  |

##### Example expressions

```
[5]EQU[4] // 5 == 4
```

```
[i]LT[10] // index < 10
```

```
[i]LT[10]AND[i]GTE[4] // (index < 10) && (index >= 4)
```

```
[i]LT[10]AND[i]GTE[4]OR[i]LT[8] // (index < 10) && ((index >= 4) || (index < 8))
```

#### Example loops

```
++++{[$i]GT[0]^n_-}
// Summary: Outputs "4 3 2 1".
// Sets the value at index 0 to 4.
// Checks the value at the current index (0).
// Shows the value at the current index (0) as a number, and then a space character.
// Decrements the value at the current index (0).
```

```
++++{[$i]GT[0]([1]$[$i]){[$i1]GT[0]^n_([1]-[1])}-}
// Summary: Outputs "4 4 4 4 3 3 3 2 2 1"
// Sets the value at index 0 to 4.
// Checks the value at the current index (0).
// Copies the value at the current index (0) to the index 1.
// Shows the value at the current index (0) as a number, and then a space character, while the value at index 1 is not 0.
// Subtracts 1 from the element at the index 1.
// Loops until the value at the index 1 is 0.
// Decrements the value at the current index (0).
```

### Files

By default, the interpreter receives input from `STDIN` and outputs to `STDOUT`. However, you can redirect the input/output stream to files.

#### Opening Files

The `FILE_OPEN` instruction tells the interpreter to redirect the input/output to a file:

* To redirect the input, use `v` (_i.e. `Fv"PATH/TO/FILE"`_).

* To redirect the output, use `^` (_i.e. `F^"PATH/TO/FILE"`_).

> If the file doesn't exist, it will be created.

#### Closing Files

Similarly, the `FILE_CLOSE` instruction tells the interpreter to stop redirecting the input/output to a file:

* To stop redirecting the input, use `v` (_i.e. `fv`_).

* To stop redirecting the output, use `^` (_i.e. `f^`_).

After the redirecting is stopped, the interpreter uses the default input/output stream again.

> Executing the `FILE_CLOSE` instruction on the input/output stream, when no file is open on that particular stream, will raise an exception.
>
> Files are automatically closed after the script is executed, even if the script doesn't include a `FILE_CLOSE` instruction.
## Example Scripts

```
+++++^n
// Summary: Outputs "5".
// Sets the value at index 0 to 5, and outputs it as a number.
```

```
V^
// Summary: Outputs the input as a character.
// Reads and replaces the value at index 0 with the input, and outputs it as a character.
```

```
V^c_n\
// Summary: Outputs the input as a character and as a number.
// Reads and replaces the value at index 0 with the input.
// Outputs the value as a character.
// Outputs a space.
// Outputs the value as a number.
// Outputs a `\n` character.
```

```
++++++++++&^
// Summary: Outputs the result of AND(10, input).
// Sets the value at index 0 to 10, then sets it to AND(10, input) and outputs it.
```

```
($[72])>($[101])>($[108])>($[108])>($[111])>($[32])>($[87])>($[111])>($[114])>($[108])>($[100])>($[33])<<<<<<<<<<<^>^>^>^>^>^>^>^>^>^>^>^
// Summary: Outputs "Hello World!".
// Sets the value at index 0 to 72, increments the index, sets the value at index 1 to 101 and so on. . .
// Decrements the index 11 times, so it becomes 0.
// Outputs all the values from index 0 to 11.
```

```
V(+[10])^n
// Summary: Outputs input + 10.
// Sets the value at index 0 to input, adds 10 to it, and then outputs it as a number.
```

```
V([0]+[10])^n
// Summary: Outputs input + 10 (alternative way).
// Sets the value at index 0 to input, adds 10 to it (by reffering to the value at the index 0), and then outputs it as a number.
```