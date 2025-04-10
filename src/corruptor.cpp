#include "corruptor.h"
#include <ctime>
#include <stdexcept>

namespace corruptor {

    std::set<size_t> selector(
        const size_t &length,
        const int &quantity) {
            // Selects specified quanity of non-repeating indexes in range [0, length)
            if (length < 1) {
                throw std::invalid_argument("Length must be at least 1.");
            }
            srand(std::time(NULL));
            std::set<size_t> selected;
            while (selected.size() < quantity) {
                selected.insert(rand() % length);
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


}

}  // namespace corruptor
