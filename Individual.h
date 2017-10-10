#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

typedef unsigned char byte;

#include <stdint-gcc.h>

class Individual {
public:
    explicit Individual(int size);
    void toString();
    int getFitness();
    int getSize();
    void crossover(Individual *pIndividual);
    void mutate();
    int* getChromosomes();
    int* setChromosomes(int* chromosome);

private:
    int* chromosome;
    int size;
    int fitness;
};


#endif //GENETICALGORITHM_INDIVIDUAL_H