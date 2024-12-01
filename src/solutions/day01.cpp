/**
 * https://adventofcode.com/2024/day/1
*/

#include <aoc2024/solution.hpp>

#include <string>
#include <iostream>
#include <print>
#include <algorithm>
#include <ranges>
#include <utility>
#include <vector>
#include <span>
#include <map>

#include <cstddef>
#include <cstdint>
#include <cmath>

static constexpr std::size_t AOC_INPUT_SIZE = 1000uz;

auto extract_lists(std::istream& input_stream)
    -> std::pair<std::vector<std::uint32_t>, std::vector<std::uint32_t>>
{
    auto left = std::vector<std::uint32_t>();
    auto right = std::vector<std::uint32_t>();

    left.reserve(AOC_INPUT_SIZE);
    right.reserve(AOC_INPUT_SIZE);

    uint32_t l, r;
    while (input_stream >> l >> r)
    {
        left.push_back(l);
        right.push_back(r);
    }

    return std::make_pair(left, right);
}

auto aoc2024::solve_a(std::istream& input_stream) -> void {
    auto [left, right] = extract_lists(input_stream);

    std::ranges::sort(left);
    std::ranges::sort(right);

    auto sum_of_distances = 0uz;
    for (auto i = 0uz; i < left.size(); ++i) {
        const auto diff = (std::int32_t)(left[i] - right[i]);
        const auto distance = std::abs(diff);

        sum_of_distances += distance;
    }

    std::println("{}", sum_of_distances);
}

auto count_occurrences(const std::span<const std::uint32_t> values, const std::uint32_t key)
    -> std::size_t
{
    // Maps a `key` to the number of times it appears in `values`.
    static auto _occurrence_lookup = std::map<std::uint32_t, std::size_t>();

    // Scan the lookup for the `key`, if found, return its number of occurrences
    if (const auto it  = _occurrence_lookup.find(key); it != _occurrence_lookup.end()) {
        const auto& [_, n] = *it;
        return n;
    }

    // Otherwise, compute the number of occurrences, store it in the lookup, then return it
    return (_occurrence_lookup[key] = std::ranges::count(values, key));
}

auto aoc2024::solve_b(std::istream& input_stream) -> void {
    const auto [left, right] = extract_lists(input_stream);

    auto sum_of_similarities = 0uz;
    for (const auto& value : left) {
        const auto n = count_occurrences(right, value);

        const auto similarity_score = (value * n);

        sum_of_similarities += similarity_score;
    }

    std::println("{}", sum_of_similarities);
}
