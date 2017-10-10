#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Population.h"
#include "config.h"

int main() {
    /* initialize random seed: */
    srand (time(nullptr));

    // Create the results file and enter the configuration values
    std::ofstream resultsFile;
    time_t now = time(0);
    char* dt = ctime(&now);
    std::ostringstream path;
    path << "../data/results_" << dt << ".csv";
    resultsFile.open(path.str(), std::ios_base::app);

    if (resultsFile.is_open()) {
        resultsFile << NUMBER_OF_GENERATIONS << ","
                    << NUMBER_OF_CHROMOSONES << ","
                    << SIZE_OF_POPULATION << ","
                    << PROBABILITY_OF_CROSSOVER << ","
                    << PROBABILITY_OF_MUTATION;

        resultsFile.close();
    } else {
        std::cout << "Could not write to the results file, end \n";
        return 0;
    }

    // Create main population that we will be generating
    auto* population = new Population();

    // Temp population to store values of population of a single generation
    Population* tempPopulation;

    // Seed the first population randomly
    population->generate(NUMBER_OF_CHROMOSONES);

    // Loop over the number of generations and evolve the GA
    for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {
        std::cout << "Generation: " << i + 1 << "\n";
        tempPopulation = population
                ->selectParents() // First, let's perform tournament selection and create a new population of the fittest
                ->crossover() // Now, pair the individuals and perform crossover
                ->mutate() // Once crossover is done, run mutation to randomly flip bits
                ->printStats(path.str()); // Print stats for logging purposes

        // So that we can ensure the strongest of the previous generation survive, lets copy it over from the previous selection
        tempPopulation->replaceWeakestIndividual(population->getFitestIndividual());
        // Assign the new population to the original
        population = tempPopulation;
    }

    return 0;
}