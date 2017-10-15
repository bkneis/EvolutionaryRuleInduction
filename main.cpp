#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Population.h"
#include "config.h"

/**
 * Create a results file to save the fitness values to per generation. Then return the file path.
 * @return path
 */
std::string createResultsFile() {
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
        return path.str();
    }

    throw "Could not write to the results file";
}

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
    auto* population = new Population<>();

    // Temp population to store values of population of a single generation
    Population<>* tempPopulation;

    Individual<>* fittestIndividual;

    // Seed the first population randomly
    population->generate(SIZE_OF_POPULATION);

    // Loop over the number of generations and evolve the GA
    for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {
        std::cout << "Generation: " << i + 1 << "\n";
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
        population->printStats(resultsPath);
    }

    return 0;
}