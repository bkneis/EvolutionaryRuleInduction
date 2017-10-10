#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include <vector>
#include "Individual.h"

class Population {

public:
    std::vector<Individual*> individuals;
    int getMaxFitness();
    int getMeanFitness();
    void toString();
    void generate(int size);
    void addIndividual(Individual* individual);
    Population* calcStats();
    Population* selectParents();
    Population* crossover();
    Population* mutate();
    Population* printStats(std::string path);
    Individual* getFitestIndividual();
    Population* replaceWeakestIndividual(Individual* fittest);

private:
    int maxFitness;
    int meanFitness;
};


#endif //GENETICALGORITHM_POPULATION_H
