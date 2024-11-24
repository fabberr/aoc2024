#!/usr/bin/env sh

################################################################################
############################### CONTROL VARIABLES ##############################
################################################################################

# Version
SCRIPT_NAME="aoc2024.sh"
SCRIPT_VERSION="$SCRIPT_NAME v1.2.0"

# Command Type Enum
COMMAND_TYPE_NEW="new"
COMMAND_TYPE_RUN="run"

################################################################################
################################## FUNCTIONS ###################################
################################################################################

# Summary:
#     Prints help information to stdout.
print_help() {
    cat <<- EOF
	NAME
	    $SCRIPT_NAME - Create, build and run solutions for Advent of Code 2024
	    puzzles written in C++.

	SYNOPSIS
	    $SCRIPT_NAME [options] <command> <solution> [args]

	    $SCRIPT_NAME new <solution>
	    $SCRIPT_NAME run <solution> [args]

	OPTIONS
	    --version, -v
	        Displays the version of the script and exits.

	    --help, -h, -?, ?
	        Displays this help message and exits.

	COMMANDS
	    new <solution>
	        Creates a new solution with the specified name.

	        Arguments:

	            <solution> (required)
	                The name of the solution to create.

	        This will generate:

	            1. A new C++ file implementing \`include/aoc2024/solution.hpp\`
	               under the \`src/solutions/\` directory.

	            2. An empty input file under the \`src/input/\` directory.

	            3. Make targets for building and running the new solution.
	               If the targets already exist, this step is skipped.

	    run <solution> [args]
	        Runs the specified solution. The solution must exist.

	        Arguments:

	            <solution> (required)
	                The name of the solution to execute.

	            [args] (optional)
	                Additional arguments to be forwarded to the solution.

	AUTHORS
	    Fabrício Milanez (https://github.com/fabberr)
	EOF
}

# Summary:
#     Creates a new solution with the specified name.
#
# Arguments:
#     $1 - solution_name
#         The name of the new solution.
new_solution() {

    # Parameters
    local solution_name="$1"

    # Directories
    local source_dir="./src"
    local solution_dir="$source_dir/solutions"
    local input_dir="$source_dir/input"

    # Create input file    
    mkdir -p "$input_dir"
    
    touch "$input_dir/${solution_name}.txt"

    # Create source file
    mkdir -p "$solution_dir"

    cat <<- EOF > "$solution_dir/${solution_name}.cpp"
	#include <aoc2024/solution.hpp>

	#include <string>
	#include <iostream>

	auto aoc2024::solve_a(std::istream& input_stream) -> void {
	    for (std::string line{}; std::getline(input_stream, line, '\\n') and line != ""; ) {
	        // @todo: Implement solution for first puzzle
	    }
	}

	auto aoc2024::solve_b(std::istream& input_stream) -> void {
	    for (std::string line{}; std::getline(input_stream, line, '\\n') and line != ""; ) {
	        // @todo: Implement solution for second puzzle
	    }
	}
	EOF

    # Create Makefile targets, if needed
    if cat "./Makefile" | grep -qE "${solution_name}:"; then
        return
    fi

    build_target_name="\$(BUILD_DIR)/${solution_name}"
    build_prerequisites="${source_dir}/main.cpp ${solution_dir}/${solution_name}.cpp"

    printf "\n# Build target ${solution_name}\n"                  >> "./Makefile"
    printf "%s: %s\n" "$build_target_name" "$build_prerequisites" >> "./Makefile"
    printf "\tmkdir -p \$(BUILD_DIR)\n"                           >> "./Makefile"
    printf "\t\$(CPP) \$(CPP_FLAGS) -o \$@ \$^\n"                 >> "./Makefile"

    printf "\n# Run target ${solution_name}\n"          >> "./Makefile"
    printf "run-${solution_name}: $build_target_name\n" >> "./Makefile"
    printf "\t\$< src/input/day00.txt \$(ARGS)\n"       >> "./Makefile"
}

# Summary:
#     Runs the specified solution. The solution must exist.
#
# Arguments:
#     $1 - solution_name
#         The name of the solution to execute.
#
#     @:2 - args
#         The command line arguments to forward to the solution, if any.
run_solution() {
    # Parameters
    local solution_name="$1"; shift
    local args="$@"

    make --silent ARGS="$args" "run-${solution_name}"
}

################################################################################
################### EXTRACT AND PARSE COMMAND LINE ARGUMENTS ###################
################################################################################

if [ ! -d "src" ]; then
    echo "Error: The script must be executed from the root directory."
    exit 1
fi

case "$1" in
    --version|-v)
        echo "$SCRIPT_VERSION"
        exit 0
        ;;
    --help|-h|-?|?)
        print_help
        exit 0
        ;;
    "$COMMAND_TYPE_NEW")
        if [ $# -lt 2 ]; then
            echo "Usage: $0 $COMMAND_TYPE_NEW <solution>"
            exit 1
        fi
        new_solution "$2"
        shift
        ;;
    "$COMMAND_TYPE_RUN")
        if [ $# -lt 2 ]; then
            echo "Usage: $0 $COMMAND_TYPE_RUN <solution> [args]"
            exit 1
        fi
        run_solution "$2" "${@:3}"
        shift
        ;;
    *)
        echo "Unrecognized command '$1'."
        exit 1
        ;;
esac
