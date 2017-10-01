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
    explicit Population(int size);
    void getMaxFitness();
    void toString();

private:
    void generate(int size);
};


#endif //GENETICALGORITHM_POPULATION_H
