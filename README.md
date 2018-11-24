# About
_Exomit_ is a scripting language whose main goal is to be hard to understand.

This is a cross-platform interpreter for Exomit written in C++.

# License
The Exomit language was created by [UnexomWid](http://unexomwid.me).

The Exomit, Exomit Interpreter, and all pieces of software that interact with Exomit, are licensed under the [GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html) license.

# Exomit
Exomit consists of an instruction pointer (called _index_), a moveable data pointer (called _pointer_) and multiple instructions.

The pointer contains references to bytes (called _values_) and is implemented with `std::vector`. Each value represents the ASCII code of a character.

Each instruction has an _identifier_ (represented by a character) and a _body_ (represented by a function).

The body of an instruction can perform actions on the index, the pointer and on the input stream.

## Using the interpreter

The Exomit Interpreter accepts command-line arguments.

The first argument *must* be the script file to execute.

Other arguments are in the form of numbers, and are optional. These are used to initialize the vector of values.

### Examples

```
exomit test.exmi
// Executes the "test.exmi" script.
```

```
exomit test.exmi 50 1 125 9 74
// Sets the value at index 0 to 50, the value at index 1 to 1 and so on. . .
// Executes the "test.exmi" script.
```

## List of instructions

|   Instruction   | Identifier |                                                                                                                                                                                               Description                                                                                                                                                                                              |
|:---------------:|:----------:|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| VALUE_INCREMENT |      +     |                                                                                                                                                                                Increments the value at the current index                                                                                                                                                                               |
| VALUE_DECREMENT |      -     |                                                                                                                                                                                Decrements the value at the current index                                                                                                                                                                               |
| VALUE_OPERATION | (OP[NUM])  | Executes an operation on the value at the current index. See below _OP_ and _[NUM]_                                                                                                                                                                                                                                                                                                                    |
| INDEX_INCREMENT | >          | Increments the index                                                                                                                                                                                                                                                                                                                                                                                   |
| INDEX_DECREMENT | <          | Decrements the index                                                                                                                                                                                                                                                                                                                                                                                   |
| STDOUT_WRITE    | ^          | Writes the value at the current index to STDOUT, as a character. Also searches forwards for other characters (without square brackets): [c] prints the current value as a character, [n] prints the current value as a number, [_] prints a space, [\] prints the `\n` character. See below _Script Examples_                                                                                          |
| STDIN_READ      | V          | Sets the value at the current index to the input from STDIN                                                                                                                                                                                                                                                                                                                                            |
| STDIN_ADD       | v          | Adds the input from STDIN to the value at the current index                                                                                                                                                                                                                                                                                                                                            |
| STDIN_XOR       | x          | Sets the value at the current index to XOR(STDIN_input, value)                                                                                                                                                                                                                                                                                                                                         |
| STDIN_AND       | &          | Sets the value at the current index to AND(STDIN_input, value)                                                                                                                                                                                                                                                                                                                                         |
| STDIN_OR        | \|          | Sets the value at the current index to OR(STDIN_input, value)                                                                                                                                                                                                                                                                                                                                          |

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
|     x     | Sets the value to the result of XOR(value, [NUM]) |
|     &     | Sets the value to the result of AND(value, [NUM]) |
|     \|     |  Sets the value to the result of OR(value, [NUM]  |

### [NUM]

Represents a number, in square brackets. A `[NUM]` may include another `[NUM]` (see below).

#### Examples

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
V^c_n\\
// Summary: Outputs the input as a character and as a number.
// Reads from STDIN and replaces the value at index 0 with the input (STDIN_input).
// Outputs the value as a character.
// Outputs a space.
// Outputs the value as a number.
// Outputs 2 `\n` characters.
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