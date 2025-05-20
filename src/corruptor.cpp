#include "corruptor.h"
#include <stdexcept>
#include <random>

// TODO: verify inverter's functionality

namespace corruptor {

    std::set<std::size_t> selector(
        const std::size_t &length,
        const int &quantity) {
        // Selects specified quanity of non-repeating indexes in range [0, length)

        if (length < 1) {
            throw std::invalid_argument("[corruptor::selector] Length must be at least 1.");
        }

        if (quantity > length) {
            throw std::invalid_argument("[corruptor::selector] Quantity must not exceed length.");
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, length - 1);
        std::set<std::size_t> selected;
        while (selected.size() < quantity) {
            selected.insert(distr(gen));
        }
        return selected;
    }

    std::vector<unsigned int> inverter(
        const std::uint8_t bits_per_char,
        const std::vector<unsigned int> &compressed,
        const Range &bits_per_inversion,
        const Range &inversions) {

        if (    bits_per_inversion.start > bits_per_inversion.end
            ||  inversions.start > inversions.end) {
            throw std::invalid_argument("[corruptor::inverter] Start of Range must be no greater than its end.");
        }

        if (bits_per_inversion.end > bits_per_char) {
            throw std::invalid_argument("[corruptor::inverter] Inversion range exceed bits per character.");
        }

        int inversion_to_perform;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(inversions.start, inversions.end);
        inversion_to_perform = distr(gen);
        std::set<std::size_t> selected = selector(compressed.size(), inversion_to_perform);

        std::vector<unsigned int> inverted(compressed);
        std::uniform_int_distribution<> distr_bits(bits_per_inversion.start, bits_per_inversion.end);
        for (auto idx : selected) {
            int bits_to_invert = distr_bits(gen);
            int position;
            
            if (bits_to_invert == bits_per_char) {
                position = 0;
            } else {
                std::uniform_int_distribution<> distr_pos(0, bits_per_char - bits_to_invert - 1);
                position = distr_pos(gen);
            }

            int mask = ((1 << bits_to_invert) - 1) << position;
            inverted[idx] = inverted[idx] ^ mask;
        }
        return inverted;
    }

    std::vector<unsigned int> swapper(
        const std::vector<unsigned int> &compressed,
        const Range &positions_to_swap) {
        
        if (positions_to_swap.start > positions_to_swap.end) {
            throw std::invalid_argument("[corruptor::swapper] Start of Range must be no greater than its end.");
        }

        int swaps_to_perform;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(positions_to_swap.start, positions_to_swap.end);
        swaps_to_perform = distr(gen);
        std::set<std::size_t> selected = selector(compressed.size(), swaps_to_perform);

        std::uniform_int_distribution<> distr2(0, compressed.size() - 1);
        std::vector<unsigned int> swapped(compressed);
        for (auto idx : selected) {
            // Can swap with itself, but for more than 1 swap
            // the result could just end up being the input anyway without complex checks
            std::swap(swapped.at(idx), swapped.at(distr2(gen)));
        }
        return swapped;
    }

}  // namespace corruptor
