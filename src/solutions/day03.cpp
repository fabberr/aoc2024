/**
 * https://adventofcode.com/2024/day/3
*/
#include <aoc2024/solution.hpp>

#include <string>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <expected>
#include <system_error>
#include <print>
#include <array>

#include <cstddef>
#include <cstdint>
#include <cstdio>

using namespace std::string_view_literals;

static constexpr std::size_t AOC_INPUT_SIZE = 1uz;

enum class binary_operator_t : char {
    none = '\0',
    multiply = '*',
};

struct operands_t {
    std::int32_t x = {};
    std::int32_t y = {};
};

// Demo: https://godbolt.org/z/ac3cPo94Y
struct binary_expression_t {
    binary_operator_t operator_type = binary_operator_t::none;
    operands_t operands = {};

    auto operator()() const
        -> std::expected<std::int32_t, std::errc>
    {
        const auto& [x, y] = operands;

        switch (operator_type) {
        case binary_operator_t::multiply:
            return (x * y);
        case binary_operator_t::none:
        default:
            return std::unexpected(std::errc::operation_not_supported);
        }
    }
};

auto extract_expression(std::string_view input)
    -> binary_expression_t
{
    static constexpr std::string_view key = "mul("sv;

    std::size_t pos = 0uz;
    while ((pos = input.find(key, pos)) < std::string_view::npos)
    {
        std::println("Found from {} to {}\n", pos + 1, pos + key.size() + 1);
        pos = input.find(key, pos + key.size());

        /**
         * 1. Store a collection of the indexes where `mul(` occurrences END.
         *      Each entry signals the START of a possible expression.
         * 2. For each START index, iterate over the string until either:
         *      a) We step outside the bounds of the string.
         *      b) We go over the maximum number of iterations (7).
         *          "It does that with instructions like mul(X,Y), where X and Y are each 1-3 digit numbers"
         *          2 (operands) * 3 (max len each) + 1 (comma) = 7 max
         *      c) A `)` token is found.
         * 3. After iterating, if a `)` token was found, we have an EXPRESSION -> store it.
         *      Store it as a slice (std::span<std::string_view::value_type>) to avoid further allocations.
         * 4. For each EXPRESSION, attempt to extract and parse both operands.
         *      a) If successful, we have a VALID EXPRESSION.
         *      b) Otherwise, discard it.
         * 5. For each VALID EXPRESSION, evaluate it.
         *      Creating a new instance of `binary_expression_t` with both operands and
         *      the operator, then invoke its function call operator overload.
        */
    }

    return {};
}

auto aoc2024::solve_a(std::istream& input_stream) -> void {
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != ""; ) {
        extract_expression(line);
    }
}

auto aoc2024::solve_b(std::istream& input_stream) -> void {
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != ""; ) {
        // @todo: Implement solution for second puzzle
    }
}
