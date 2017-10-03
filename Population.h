//
// Created by arthur on 29/09/17.
//

#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include <vector>
#include "Individual.h"

class Population {

public:
    std::vector<Individual*> individuals;
    Population* selectParents();
    Population* crossover();
    Population* mutate();
    Population* printStats();
    int getMaxFitness();
    int getMeanFitness();
    void toString();
    void generate(int size);
    void addIndividual(Individual* individual);
    Population* calcStats();

private:
    int maxFitness;
    int meanFitness;
};


#endif //GENETICALGORITHM_POPULATION_H
