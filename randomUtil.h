#ifndef GENETICALGORITHM_RANDOMUTIL_H
#define GENETICALGORITHM_RANDOMUTIL_H

#include <cstdlib>

inline int getRandomNumber(int min, int max) {
    return rand() % (max + 1) + min;
}

#endif //GENETICALGORITHM_RANDOMUTIL_H
