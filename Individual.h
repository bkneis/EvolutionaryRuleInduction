#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <stdint-gcc.h>

enum fitnessStrategy { COUNTING_ONES, SQUARED };

class Individual {
public:
    explicit Individual(int size, fitnessStrategy strategy);
    void toString();
    int getFitness();
    int getSize();
    void crossover(Individual *pIndividual);
    void mutate();
    int* getChromosomes();
    int* setChromosomes(int* chromosome);
    fitnessStrategy getFitnessStrategy();

private:
    int getFitnessCountingOnes();
    int getFitnessSquared();
    int* chromosome;
    int size;
    int fitness;
    fitnessStrategy fitnessStrat;
};


#endif //GENETICALGORITHM_INDIVIDUAL_H
