#pragma once

#include <vector>
#include <set>

namespace corruptor {

    // C++17 does not have ranges as part of standard library
    struct Range {
        const int start;
        const int end;
    };

    std::set<size_t> selector(
        const size_t &length,
        const int &quantity);

    std::vector<unsigned int> inverter(
        const std::vector<unsigned int> &compressed,
        const Range &bits_per_inversion,
        const Range &inversions);

    // TODO: Swapper?

}  // namespace corruptor
