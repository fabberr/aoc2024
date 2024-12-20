/**
 * https://adventofcode.com/2024/day/3
*/
#include <aoc2024/solution.hpp>

#include <string>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <expected>
#include <optional>
#include <system_error>
#include <print>
#include <array>
#include <vector>
#include <regex>
#include <charconv>
#include <numeric>

#include <cstddef>
#include <cstdint>
#include <cstdio>

using namespace std::string_view_literals;

static constexpr std::size_t AOC_INPUT_SIZE = 6uz;

enum class operator_t : char {
    none = '\0',
    multiply = '*',
};

typedef struct operands {
    std::int32_t lhs = {};
    std::int32_t rhs = {};
} operands_t;

// Demo: https://godbolt.org/z/ac3cPo94Y
typedef struct expression {
    operator_t operator_type = operator_t::none;
    operands_t operands = {};

    auto operator()() const
        -> std::expected<std::int32_t, std::errc>
    {
        const auto& [lhs, rhs] = operands;

        switch (operator_type) {
        case operator_t::multiply:
            return (lhs * rhs);
        case operator_t::none:
        default:
            return std::unexpected(std::errc::operation_not_supported);
        }
    }
} expression_t;

template<typename TValue>
bool try_parse(std::string_view string_value, TValue& out_result) {
    // Implicit conversion from `std::from_chars_result` to `bool` requires C++26 standard.
    if (not std::from_chars(string_value.data(), string_value.data() + string_value.size(), out_result))
    {
        return false;
    }
    return true;
}

auto string_split(std::string_view string, char separator)
    -> std::vector<std::string_view>
{
    const auto parts = string
        | std::views::split(separator)
        | std::ranges::to<std::vector>();

    auto result = std::vector<std::string_view>();
    for (const auto& part : parts) {
        result.emplace_back(part.data());
    }

    return result;
}

auto parse_expression(std::string_view expression)
    -> std::optional<expression_t>
{
    constexpr static auto EXPRESSION_START_TOKEN_SIZE   = "mul("sv.size();
    constexpr static auto EXPRESSION_END_TOKEN_SIZE     = ")"sv.size();

    if (not expression.starts_with("mul("sv) or not expression.ends_with(')')) {
        return std::nullopt;
    }

    expression.remove_prefix(EXPRESSION_START_TOKEN_SIZE);
    expression.remove_suffix(EXPRESSION_END_TOKEN_SIZE);

    const auto parts = string_split(expression, ',');
    
    if (parts.size() < 2) {
        return std::nullopt;
    }

    std::int32_t lhs;
    if (not try_parse(parts[0], lhs)) {
        return std::nullopt;
    }

    std::int32_t rhs;
    if (not try_parse(parts[1], rhs)) {
        return std::nullopt;
    }

    return expression_t {
        .operator_type = operator_t::multiply,
        .operands = {
            .lhs = lhs,
            .rhs = rhs
        },
    };
}

auto extract_expressions(std::string_view input)
    -> std::vector<expression_t>
{
    static constexpr std::size_t max_expression_size = 7uz;
    static constexpr std::string_view key = "mul("sv;

    auto raw_expressions = std::vector<std::string_view>();

    std::size_t pos = 0uz;
    while ((pos = input.find(key, pos)) < std::string_view::npos)
    {
        const std::size_t start = (pos + key.length());

        std::size_t i = start, count = 0uz;
        while (
            i < input.size() and
            count < max_expression_size and
            input[i] != ')'
        )
        { ++i; ++count; }

        if (')' == input[i]) {
            const auto end = start - pos + count + 1;
            raw_expressions.emplace_back(input.substr(pos, end));
        }

        pos = start;
    }

    auto valid_expressions = raw_expressions
        | std::views::transform(parse_expression)
        | std::views::filter([](const auto& expr) { return expr.has_value(); })
        | std::views::transform([](const auto& expr) { return expr.value(); })
        | std::ranges::to<std::vector>();
    
    return valid_expressions;
}

auto aoc2024::solve_a(std::istream& input_stream) -> void {

    std::int32_t sum = 0;
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != ""; ) {
        const auto expressions = extract_expressions(line);

        const auto results = expressions
            | std::views::transform([](const auto& expr) { return expr(); })
            | std::views::transform([](const auto& result) { return result.value_or(0); })
            | std::ranges::to<std::vector>();

        sum += std::accumulate(results.begin(), results.end(), 0, std::plus<int>());
    }

    std::println("{}", sum);
}

auto aoc2024::solve_b(std::istream& input_stream) -> void {
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != ""; ) {
        // @todo: Implement solution for second puzzle
    }
}
