#pragma once

#include <vector>
#include <set>
#include <cstddef>

namespace corruptor
{

    // C++17 does not have ranges as part of standard library
    struct Range
    {
        const int start;
        const int end;
    };

    std::set<std::size_t> selector(
        const std::size_t &length,
        size_t &quantity);

    std::vector<unsigned int> inverter(
        const std::uint8_t bits_per_char,
        const std::vector<unsigned int> &compressed,
        const Range &bits_per_inversion,
        const Range &inversions);

    std::vector<unsigned int> swapper(
        const std::vector<unsigned int> &compressed,
        const Range &positions_to_swap);

} // namespace corruptor
