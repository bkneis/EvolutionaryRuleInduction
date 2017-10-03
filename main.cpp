
#include <cstdlib>
#include <iostream>
#include "Population.h"
#include "config.h"
#include "randomUtil.h"

int main() {
    /* initialize random seed: */
    srand (time(NULL));

    auto * population = new Population();
    population->generate(NUMBER_OF_CHROMOSONES);

    for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {
        std::cout << "Generation: " << i << "\n";
        population = population
                ->selectParents()
                ->crossover()
                ->mutate()
                ->printStats();
    }
    return 0;
}