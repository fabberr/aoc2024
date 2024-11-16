/**
 * File: day00.cpp
 * 
 * This is a sample source file that implements solution.hpp
*/
#include <aoc2024/solution.hpp>

#include <string>
#include <iostream>
#include <print>
#include <stack>

auto aoc2024::solve_a(std::istream& input_stream) -> void {
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != ""; ) {
        std::println("{}", line);
    }
}

auto aoc2024::solve_b(std::istream& input_stream) -> void {
    auto stack = std::stack<std::string>();

    for (std::string line{}; std::getline(input_stream, line, '\n') and line != ""; ) {
        stack.push(line);
    }

    while (not stack.empty()) {
        std::println("{}", stack.top());
        stack.pop();
    }
}
