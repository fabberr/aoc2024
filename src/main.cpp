#include <aoc2024/aoc2024.hpp>

#include <cstdlib>

#include <filesystem>
#include <fstream>
#include <string_view>
#include <vector>
#include <print>

using namespace std::string_view_literals;
namespace fs = std::filesystem;

/**
 * @brief Pointer-to-function type.
 * 
 * @param std::istream& Reference to a valid std::istream object.
*/
using solution_fn = void (*)(std::istream&);

auto main(int argc, char* argv[]) -> int {
    const auto args = std::vector<std::string_view>(argv, argv + argc);

    if (argc < 3) {
        std::println("Usage: {} <input_filename> <solution>", args.at(0));
        return EXIT_FAILURE;
    }

    const char part = args.at(2).at(0);
    solution_fn solve = nullptr;
    switch (part) {
        case 'a':
            solve = &aoc2024::solve_a;
            break;
        case 'b':
            solve = &aoc2024::solve_b;
            break;
        default:
            std::println("Error: Invalid value '{}' for argument <solution>.", part);
            return EXIT_FAILURE;
    }

    const fs::path input_path = args.at(1);
    if (std::ifstream input_stream(input_path); input_stream) {
        solve(input_stream);
    } else {
        std::println("Error: Unable to open file '{}' specified in argument <input_filename>.", input_path.native());
        return EXIT_FAILURE;
    }
}
