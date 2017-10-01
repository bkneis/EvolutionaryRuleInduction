//
// Created by arthur on 29/09/17.
//

#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H


#include <stdint-gcc.h>

class Individual {
public:
    explicit Individual(int size);
    void toString();
    void evaluateFitness();

private:
    uint8_t * chromosome;
    int size;
    int fitness;
};


#endif //GENETICALGORITHM_INDIVIDUAL_H
