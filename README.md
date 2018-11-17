# About
_Exom CrypticScript_ (or _EXCS_ for short) is a scripting language whose main goal is to be hard to understand.

EXCS Interpreter is a cross-platform interpreter for Exom CrypticScript written in C++.

# License
The _Exom CrypticScript_ language was created by [UnexomWid](http://unexomwid.me).

The _Exom CrypticScript_ _EXCS Interpreter_, and all pieces of software that interact with _EXCS_, are licensed under the [GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html) license.

# Exom CrypticScript
_EXCS_ consists of an instruction pointer (called _index_), a moveable data pointer (called _pointer_) and multiple instructions.

The pointer contains references to bytes (called _values_). Each value represents the ASCII code of a character.

Each instruction has an _identifier_ (represented by a character) and a _body_ (represented by a function).

The body of an instruction can perform actions on the index, the pointer and on the input stream.

## List of instructions

|   Instruction   | Identifier |                                                                                                                                                                                               Description                                                                                                                                                                                              |   |   |
|:---------------:|:----------:|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:-:|:-:|
| VALUE_INCREMENT |      +     |                                                                                                                                                                                Increments the value at the current index                                                                                                                                                                               |   |   |
| VALUE_DECREMENT |      -     |                                                                                                                                                                                Decrements the value at the current index                                                                                                                                                                               |   |   |
| VALUE_OPERATION | ([O][NUM]) | Executes an operation on the value at the current index [O] = operation [NUM] = number  List of operations: [$] sets the value to [NUM] [+] adds [NUM] to the value [-] subtracts [NUM] from the value [/] divides the value by [NUM] [x] sets the value to the result of XOR(value, [NUM]) [&] sets the value to the result of AND(value, [NUM]) [|] sets the value to the result of OR(value, [NUM]) |   |   |
| INDEX_INCREMENT | >          | Increments the index                                                                                                                                                                                                                                                                                                                                                                                   |   |   |
| INDEX_DECREMENT | <          | Decrements the index                                                                                                                                                                                                                                                                                                                                                                                   |   |   |
| STDOUT_WRITE    | ^          | Writes the value at the current index to STDOUT, as a character                                                                                                                                                                                                                                                                                                                                        |   |   |
| STDIN_READ      | V          | Sets the value at the current index to the input from STDIN                                                                                                                                                                                                                                                                                                                                            |   |   |
| STDIN_ADD       | v          | Adds the input from STDIN to the value at the current index                                                                                                                                                                                                                                                                                                                                            |   |   |
| STDIN_XOR       | x          | Sets the value at the current index to XOR(STDIN_input, value)                                                                                                                                                                                                                                                                                                                                         |   |   |
| STDIN_AND       | &          | Sets the value at the current index to AND(STDIN_input, value)                                                                                                                                                                                                                                                                                                                                         |   |   |
| STDIN_OR        | |          | Sets the value at the current index to OR(STDIN_input, value)                                                                                                                                                                                                                                                                                                                                          |   |   |

## Examples

```
+++++^
// Sets the value at index 0 to 5, and outputs it to STDOUT.
```

```
V^
// Reads from STDIN and replaces the value at index 0 with the input (STDIN_input), and outputs it to STDOUT.
```

```
++++++++++&^
// Sets the value at index 0 to 10, then sets it to AND(10, STDIN_input) and outputs it to STDOUT.
```

```
($72)>($101)>($108)>($108)>($111)>($32)>($87)>($111)>($114)>($108)>($100)>($33)<<<<<<<<<<<^>^>^>^>^>^>^>^>^>^>^>^
// Sets the value at index 0 to 72, increments the index, sets the value at index 1 to 101 . . .
// Decrements the index 11 times, so it becomes 0.
// Outputs all the values from index 0 to 11.
// Outputs "Hello World!".
```

```
V(+10)^
// Sets the value at index 0 to STDIN_input, adds 10 to it, and then outputs it to STDOUT.
```