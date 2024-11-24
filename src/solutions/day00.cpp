/**
 * File: day00.cpp
 * 
 * This is a sample source file implementing `solution.hpp`
*/
#include <aoc2024/solution.hpp>

#include <string>
#include <iostream>
#include <print>
#include <ranges>

auto aoc2024::solve_a(std::istream& input_stream) -> void {
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != ""; ) {
        std::println("{}", line);
    }
}

auto aoc2024::solve_b(std::istream& input_stream) -> void {
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != ""; ) {
        for (auto ch : line | std::views::reverse) {
            std::print("{}", ch);
        }
        std::println();
    }
}
