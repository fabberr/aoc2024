# Advent of Code 2024 (C++)

Solutions for [Advent of Code 2024](https://adventofcode.com/2024) puzzles written in C++.

## Solutions

Solutions are implemented by creating a new C++ source file in `src/solutions` and implementing the two functions declared `include/aoc2024/solution.hpp`, one for each of the day's puzzles. The inputs for the day should be placed in a text file located in `src/input`.

The entry point is defined in `src/main.cpp`, and already implements basic command line parsing and file handling logic.

The program accepts the following arguments:
1. `<input_filename>`: Path to the file containing the inputs for the day.
2. `<solution>`: Selects which puzzle to solve for, `a` for the first puzzle, and `b` for the second one.

A sample implementation is provided in `src/solutions/day00.cpp`, with its inputs in `src/input/day00.txt`.

## Building

To build the solution, use the following compiler flags: `-std=c++26 -Iinclude`
- Note: Only ONE implementation of `solution.hpp` should be provided.

```bash
# Ensure output directory exists and build the solution
$ mkdir -p build; g++ -std=c++26 -Iinclude -o build/dayXX ./src/main.cpp ./src/solutions/dayXX.cpp
```

## Automation

`aoc2024.sh` is a shell script for automating the process of implementing and running solutions by making use of [GNU Make](https://www.gnu.org/software/make). The script will create all the necessary files/targets for building and running solutions.

Note that the script was designed to use paths _relative to the root directory_ of this repository and will refuse to run if called from elsewhere.

The script accepts two commands:
- `new <solution>`: Cretes a new solution by creating an empty input file and the source file implementing `solution.hpp`. Two Make targets for building and running the solution will also be created.
- `run <solution> [args]`: Runs a solution with the specified command line arguments. If the executable is not found in the `build` directory, the build target is invoked first.

Example usage:

```bash
# Ensure the execute file mode bit is set for your user:
$ chmod u+x ./aoc2024.sh

# To create a new solution (e.g. Day 1 of the event):
$ ./aoc2024.sh new day01

# To build and run the first puzzle of the solution:
$ ./aoc2024.sh run day01 a
```
