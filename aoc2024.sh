#!/usr/bin/env sh

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

    cat << EOF > "$solution_dir/${solution_name}.cpp"
#include <aoc2024/solution.hpp>

#include <string>
#include <iostream>

auto aoc2024::solve_a(std::istream& input_stream) -> void {
    for (std::string line{}; std::getline(input_stream, line, '\\n') and line != ""; ) {
        // @todo: Implement solution for part one of the puzzle
    }
}

auto aoc2024::solve_b(std::istream& input_stream) -> void {
    for (std::string line{}; std::getline(input_stream, line, '\\n') and line != ""; ) {
        // @todo: Implement solution for part two of the puzzle
    }
}
EOF

    # Create Makefile targets, if needed
    build_target_name="\$(BUILD_DIR)/${solution_name}"
    build_prerequisites="${source_dir}/main.cpp ${solution_dir}/${solution_name}.cpp"

    if cat "./Makefile" | grep -qE "${solution_name}:"; then
        return
    fi

    cat << EOF >> "./Makefile"

# Build target ${solution_name}
$build_target_name: $build_prerequisites
	\$(CPP) \$(CPP_FLAGS) -o \$@ \$^

# Run target ${solution_name}
run-${solution_name}: $build_target_name
	\$< src/input/day00.txt \$(ARGS)
EOF
}

run_solution() {
    # Parameters
    local solution_name="$1"
    local args="$2"

    make --silent ARGS="$args" "run-${solution_name}"
}

# Command Type Enum
COMMAND_TYPE_NEW="new"
COMMAND_TYPE_RUN="run"

if [ $# -lt 2 ]; then
    echo "Usage: $0 <command> <solution> [args]"
    exit 1
fi

if [ ! -d "src" ]; then
    echo "Error: The script must be executed from the root directory."
    exit 1
fi
COMMAND="$1";
SOLUTION_NAME="$2";

case "$COMMAND" in
    "$COMMAND_TYPE_NEW")
        new_solution "$SOLUTION_NAME"
        shift
        ;;
    "$COMMAND_TYPE_RUN")
        run_solution "$SOLUTION_NAME" "$3"
        shift
        ;;
    *)
        echo "Unrecognized command '$1'."
        exit 1
esac
