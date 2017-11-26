#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "config.h"
#include "Population.h"

/**
 * Main function for the application to perform the GA over configured generations
 * @return appStatusCode
 */
int main() {
    /* initialize random seed: */
    srand (time(nullptr));

    // Create results file to save fitness values to
    std::string resultsPath;
    try {
        resultsPath = createResultsFile();
    } catch(const char* err) {
        std::cout << err << "\n";
        return 0;
    }

    // Create main population that we will be generating
    auto population = new Population<unsigned long>();

    // Temp population to store values of population of a single generation
    Population<unsigned long>* tempPopulation;

    Individual<unsigned long>* fittestIndividual;

    // Seed the first population randomly
    population->generate(SIZE_OF_POPULATION);

    // Loop over the number of generations and evolve the GA
    for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {
        fittestIndividual = population->cloneFittestIndividual();

        tempPopulation = population
                ->selectParents() // First, let's perform tournament selection and create a new population of the fittest
                ->crossover() // Now, pair the individuals and perform crossover
                ->mutate(); // Once crossover is done, run mutation to randomly flip bits

        // Assign the new population to the original
        population = tempPopulation;
        // Replace the weakest individual with the strongest so the max never reduces
        population->replaceWeakestIndividual(fittestIndividual);
        // Print the populations fitness stats
        if ((i + 1) % 1 == 0) {
            std::cout << "Generation: " << i + 1 << "\n";
            population->printStats(resultsPath, true);
        }
    }

    return 0;
}