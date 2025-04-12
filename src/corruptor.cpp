#include "corruptor.h"
#include <stdexcept>
#include <random>

namespace corruptor {

    std::set<size_t> selector(
        const size_t &length,
        const int &quantity) {
            // Selects specified quanity of non-repeating indexes in range [0, length)
            if (length < 1) {
                throw std::invalid_argument("Length must be at least 1.");
            }
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(0, length - 1);
            std::set<size_t> selected;
            while (selected.size() < quantity) {
                selected.insert(distr(gen));
            }
            return selected;
        }

    std::vector<unsigned int> inverter(
        const std::vector<unsigned int> &compressed,
        const Range &bits_per_inversion,
        const Range &inversions) {
        if (    bits_per_inversion.start > bits_per_inversion.end
            ||  inversions.start > inversions.end) {
            throw std::invalid_argument("Start of Range must be no greater than its end.");
        }

        int inversion_to_perform;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(inversions.start, inversions.end);
        inversion_to_perform = distr(gen);
        std::set<size_t> selected = selector(compressed.size(), inversion_to_perform);

        std::vector<unsigned int> inverted(compressed);
        std::uniform_int_distribution<> distr(bits_per_inversion.start, bits_per_inversion.end);
        for (auto idx : selected) {
            int bits_to_invert = distr(gen);

        }
        // for every to be changed:

        //   pick bits to invert

}

}  // namespace corruptor
