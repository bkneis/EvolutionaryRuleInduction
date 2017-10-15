#ifndef GENETICALGORITHM_RANDOMUTIL_H
#define GENETICALGORITHM_RANDOMUTIL_H

#include <cstdlib>

/**
 * Generate a random number of a given type between min and max
 * @tparam T
 * @param min
 * @param max
 * @return
 */
template <typename T = int>
inline T getRandomNumber(int min, int max) {
    return static_cast<T>(rand() % (max + 1) + min);
}

#endif //GENETICALGORITHM_RANDOMUTIL_H
