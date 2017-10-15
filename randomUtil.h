#ifndef GENETICALGORITHM_RANDOMUTIL_H
#define GENETICALGORITHM_RANDOMUTIL_H

#include <cstdlib>

template <typename T = int>
inline T getRandomNumber(int min, int max) {
    return static_cast<T>(rand() % (max + 1) + min);
}

#endif //GENETICALGORITHM_RANDOMUTIL_H
