<p align="center">
  <img src="img/logo.png" alt="Exomit">
</p>

# About
_Exomit_ is a scripting language whose main goal is to be cryptic and compact.

This is a cross-platform interpreter for Exomit written in C++.

# License
The Exomit language was created by [UnexomWid](http://unexomwid.me).

The Exomit, Exomit Interpreter, and all pieces of software that interact with Exomit, are licensed under the [GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html) license.

# Releases

>Note: versions with the suffix **R** are considered stable releases, while those with the suffix **D** are considered unstable.

[v1.1R](https://github.com/UnexomWid/exomit/releases/tag/v1.1R) - March 26, 2019

[v1.0R](https://github.com/UnexomWid/exomit/releases/tag/v1.0R) - January 19, 2019

# Exomit
Exomit consists of an instruction pointer (called _index_), a moveable data pointer (called _pointer_) and multiple instructions.

The pointer contains references to bytes (called _values_) and is implemented with `std::vector`. Each value represents the ASCII code of a character.

Each instruction has an _identifier_ (represented by a character) and a _body_ (represented by a function).

The body of an instruction can perform actions on the index, the pointer and on the input stream.

## Using the interpreter

The Exomit Interpreter accepts command-line arguments.

The first argument *must* be the script file to execute.

Other arguments are optional. These are used to initialize the vector of values.

The optional arguments can be in the form of numbers `-n`, characters `-c` or a single string `-s`.

The value at index 0 will always store the amount of passed arguments. The arguments will be stored at index 1 and forwards.

### Examples

```
exomit test.exit
// Executes the "test.exit" script.
```

```
exomit test.exit -n 50 1 125 9 74
// Sets the value at index 0 to 5 (because there are 5 arguments)
// Sets the value at index 1 to 50, the value at index 2 to 1 and so on. . .
// Executes the "test.exit" script.
```

```
exomit test.exit -c a b h U z L
// Sets the value at index 0 to 6 (because there are 6 arguments)
// Sets the value at index 1 to 97 ('a' = 97), the value at index 2 to 98 ('b' = 98) and so on. . .
// Executes the "test.exit" script.
```

```
exomit test.exit -s H ello
// Sets the value at index 0 to 6 (because there are 6 arguments)
// Sets the value at index 1 to 72 ('H' = 97), the value at index 2 to 32 (' ' = 32) and so on. . .
// (Note that spaces are considered characters too)
// Executes the "test.exit" script.
```

## List of instructions

| Instruction     | Identifier       | Description                                                                                                                                                                                                                                                                                                    |
|-----------------|------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| VALUE_INCREMENT | +                | Increments the value at the current index                                                                                                                                                                                                                                                                      |
| VALUE_DECREMENT | -                | Decrements the value at the current index                                                                                                                                                                                                                                                                      |
| VALUE_OPERATION | ([INDEX]OP[NUM]) | Executes an operation on the value at an index. See below _OP_ and _[NUM]_                                                                                                                                                                                                                                     |
| INDEX_INCREMENT | >                | Increments the index                                                                                                                                                                                                                                                                                           |
| INDEX_DECREMENT | <                | Decrements the index                                                                                                                                                                                                                                                                                           |
|UNCERTAINTY_START| ?EXP             | Marks the start of an uncertainty, which is executed if the expression EXP is true                                                                                                                                                                                                                             |
| UNCERTAINTY_END | !                | Marks the end of an uncertainty                                                                                                                                                                                                                                                                                |
| LOOP_START      | {EXP             | Marks the start of a loop, which is executed while the expression EXP is true                                                                                                                                                                                                                                  |
| LOOP_END        | }                | Marks the end of a loop                                                                                                                                                                                                                                                                                        |
| STDOUT_WRITE    | ^                | Writes the value at the current index to STDOUT, as a character. Also searches forwards for other characters (without square brackets): [c] prints the current value as a character, [n] prints the current value as a number, [_] prints a space, [\\] prints the `\n` character. See below _Script Examples_ |
| STDIN_READ      | V                | Sets the value at the current index to the input from STDIN                                                                                                                                                                                                                                                    |
| STDIN_ADD       | v                | Adds the input from STDIN to the value at the current index                                                                                                                                                                                                                                                    |
| STDIN_XOR       | x                | Sets the value at the current index to XOR(STDIN_input, value)                                                                                                                                                                                                                                                 |
| STDIN_AND       | &                | Sets the value at the current index to AND(STDIN_input, value)                                                                                                                                                                                                                                                 |
| STDIN_OR        | \|                | Sets the value at the current index to OR(STDIN_input, value)                                                                                                                                                                                                                                                  |

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

You can also chain expressions with no limit, using the logical operators (see below _Relational Operators_ and _Logical Operators_)

```
[*number_1*]RELATIONAL_OPERATOR[*number_2*]LOGICAL_OPERATOR[*number_3*]RELATIONAL_OPERATOR[*number_4*]
```

> Note: chained expressions are evaluated recursively. Here are some examples:
> `EXP_1` AND (`EXP_2` AND (`EXP_3` AND ...))
> `EXP_1` OR (`EXP_2` OR (`EXP_3` OR ...))
> `EXP_1` OR (`EXP_2` AND (`EXP_3` OR ...))
>
> Currently, it's not possible to do something like this:
> (`EXP_1` AND `EXP_2`) OR (`EXP_3` AND `EXP_4`)

##### List of Relational Operators

| Relational Operator              | Identifier | Description                                                                 |
|----------------------------------|------------|-----------------------------------------------------------------------------|
| RELATIONAL_EQUAL                 | EQ         | Checks whether the left number is equal to the right number                 |
| RELATIONAL_NOT_EQUAL             | NEQ        | Checks whether the left number is not equal to the right number             |
| RELATIONAL_GREATER_THAN          | GT         | Checks whether the left number is greater than the right number             |
| RELATIONAL_GREATER_THAN_OR_EQUAL | GTE        | Checks whether the left number is greater than or equal to the right number |
| RELATIONAL_LESS_THAN             | LT         | Checks whether the left number is less than the right number                |
| RELATIONAL_LESS_THAN_OR_EQUAL    | LTE        | Checks whether the left number is less than or equal to the right number    |

##### List of Logical Operators

| Logical Operator | Identifier | Description                                   |
|------------------|------------|-----------------------------------------------|
| LOGICAL_AND      | AND        | Checks whether both expressions are true      |
| LOGICAL_OR       | OR         | Checks whether at lest one expression is true |
| LOGICAL_XOR      | XOR        | Checks whether the expressions are not equal  |

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

## Example Scripts

```
+++++^n
// Summary: Outputs "5".
// Sets the value at index 0 to 5, and outputs it to STDOUT as a number.
```

```
V^
// Summary: Outputs the input as a character.
// Reads from STDIN and replaces the value at index 0 with the input (STDIN_input), and outputs it to STDOUT as a character.
```

```
V^c_n\
// Summary: Outputs the input as a character and as a number.
// Reads from STDIN and replaces the value at index 0 with the input (STDIN_input).
// Outputs the value as a character.
// Outputs a space.
// Outputs the value as a number.
// Outputs a `\n` character.
```

```
++++++++++&^
// Summary: Outputs the result of AND(10, input).
// Sets the value at index 0 to 10, then sets it to AND(10, STDIN_input) and outputs it to STDOUT.
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
// Sets the value at index 0 to STDIN_input, adds 10 to it, and then outputs it to STDOUT as a number.
```

```
V([0]+[10])^n
// Summary: Outputs input + 10 (alternative way).
// Sets the value at index 0 to STDIN_input, adds 10 to it (by reffering to the value at the index 0), and then outputs it to STDOUT as a number.
```