# Advent of Code 2024 (C++)

Solutions for [Advent of Code 2024](https://adventofcode.com/2024) puzzles written in C++.

## Solutions

Solutions are implemented by creating a new C++ source file in `src/solutions` and implementing the two functions declared `include/aoc2024/solution.hpp`, one for each of the day's puzzles. The inputs for the day should be placed in a text file located in `src/input`.

The entry point is defined in `main.cpp`, and already implements basic command line parsing and file handling logic.

The program accepts the following arguments:
1. `<input_filename>`: Path to the file containing the inputs for the day.
2. `<solution>`: Selects which puzzle to solve for, `a` for the first puzzle, and `b` for the second one.

A sample implementation is provided in `src/solutions/day00.cpp` and `src/input/day00.txt`.

## Building

To build the solution, use the following compiler arguments:
- Note: Only ONE file implementing `solution.hpp` should be compiled.

```bash
$ mkdir -p build; g++ -std=c++23 -Iinclude -o build/dayXX ./src/main.cpp ./src/solutions/dayXX.cpp
```

## Automation

`aoc2024.sh` is a shell script for automating the process of implementing and running solutions. The script will create all the necessary files/targets for building and running new solutions. Note that the script was designed to use paths relative to the root directory of the repository and will refuse to run if called from elsewhere.

The script accepts two commands:
- `new <solution>`: Adds a new solution by creating an empty input file and the source file implementing `solution.hpp`. Two new Make targets will also be added: one for building the solution and another for running it.
- `run <solution> [args]`: Runs a solution with the specified command line arguments. If the executable is not found, the solution will be built.

Example usage:

```bash
# Ensure the execute file mode bit is set for your user:
$ chmod u+x ./aoc2024.sh

# To create a new solution (e.g. Day 1 of the event):
$ ./aoc2024.sh new day00

# To build and run the first puzzle of the solution:
$ ./aoc2024.sh run day00 a
```
