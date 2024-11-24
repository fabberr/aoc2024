#!/usr/bin/env sh

################################################################################
################################## FUNCTIONS ###################################
################################################################################

# Summary:
#     Cretes a new solution.
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
############################### CONTROL VARIABLES ##############################
################################################################################

# Version
SCRIPT_VERSION="aoc2024.sh v1.1.0"

# Command Type Enum
COMMAND_TYPE_NEW="new"
COMMAND_TYPE_RUN="run"

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
