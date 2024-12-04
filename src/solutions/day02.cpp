#include <aoc2024/solution.hpp>

#include <string>
#include <string_view>
#include <sstream>
#include <iostream>
#include <print>
#include <algorithm>
#include <ranges>
#include <utility>
#include <vector>
#include <span>

#include <cstddef>
#include <cstdint>
#include <cmath>

static constexpr std::size_t AOC_INPUT_SIZE = 1000uz;

auto extract_reports(std::istream& input_stream)
    -> std::vector<std::vector<std::int32_t>>
{
    auto reports = std::vector<std::vector<std::int32_t>>();
    reports.reserve(AOC_INPUT_SIZE);

    for (std::string line{}; std::getline(input_stream, line, '\n') and line != ""; ) {
        auto str_stream = std::istringstream(line);

        auto report = std::vector<std::int32_t>();

        std::int32_t level;
        while (str_stream >> level) {
            report.emplace_back(level);
        }

        reports.emplace_back(std::move(report));
    }

    return reports;
}

auto is_report_safe(std::span<const std::int32_t> report)
    -> bool
{
    static constexpr std::int32_t MAX_SAFE_DISTANCE_THRESHOLD = 3;

    if (report.size() < 2) {
        return true;
    }

    std::size_t i = 0uz, j = 1uz;
    bool possibly_ascending = report[i] < report[j];
    while (
        (j < report.size()) and
        (possibly_ascending ? report[i] < report[j] : report[i] > report[j]) and
        (std::abs(report[i] - report[j]) <= MAX_SAFE_DISTANCE_THRESHOLD)
    ) { i++; j++; }

    return (j == report.size());
}

auto aoc2024::solve_a(std::istream& input_stream) -> void {
    const auto reports = extract_reports(input_stream);

    const auto safe_count = std::ranges::count_if(reports, is_report_safe);
    std::println("{}", safe_count);
}

auto aoc2024::solve_b(std::istream& input_stream) -> void {
}
