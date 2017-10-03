//
// Created by arthur on 29/09/17.
//

#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

typedef unsigned char byte;

#include <stdint-gcc.h>

class Individual {
public:
    explicit Individual(int size);
    void toString();
    void evaluateFitness();

private:
    byte* chromosome;
    int size;
    int fitness;
};


#endif //GENETICALGORITHM_INDIVIDUAL_H
