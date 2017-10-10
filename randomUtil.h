#ifndef GENETICALGORITHM_RANDOMUTIL_H
#define GENETICALGORITHM_RANDOMUTIL_H

//#include <random>
//#include <chrono>
#include <cstdlib>

inline int getRandomNumber(int min, int max) {
//    long seed1 = std::chrono::system_clock::now().time_since_epoch().count();
//    std::default_random_engine gen(seed1);
//    std::uniform_int_distribution<int> dist(min, max);
//    return dist(gen);
    return rand() % (max + 1);
}

#endif //GENETICALGORITHM_RANDOMUTIL_H
