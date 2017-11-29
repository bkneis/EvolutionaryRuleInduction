#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Ingester.h>
#include "config.h"
#include "Population.h"

/**
 * Main function for the application to perform the GA over configured generations
 * @return appStatusCode
 */
int main() {

    /* initialize random seed: */
    srand (time(NULL));

    // Create results file to save fitness values to
    std::string resultsPath;
    try {
        resultsPath = createResultsFile();
    } catch(const char* err) {
        std::cout << err << "\n";
        return 0;
    }

    auto ingester = new Ingester();

    int totalClassified = 0;

    int k;
    for (k = 0; k < NUMBER_OF_FOLDS; k++) {

        std::ostringstream ssTrainPath;
        ssTrainPath << "../data/fold" << k + 1 << "/train.txt";

        std::ostringstream ssTestPath;
        ssTestPath << "../data/fold" << k + 1 << "/test.txt";
        std::string path = ssTestPath.str();

        auto trainData = ingester->readFile(ssTrainPath.str().c_str());
        auto testData = ingester->readFile(ssTestPath.str().c_str());

        // Create main population that we will be generating
        auto population = new Population<unsigned long>(trainData);

        Individual<unsigned long>* fittestIndividual;

        // Seed the first population randomly
        population->generate(SIZE_OF_POPULATION);

        // Loop over the number of generations and evolve the GA
        for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {
            fittestIndividual = population->cloneFittestIndividual();

            population = population
                    ->selectParents() // First, let's perform tournament selection and create a new population of the fittest
                    ->crossover() // Now, pair the individuals and perform crossover
                    ->mutate() // Once crossover is done, run mutation to randomly flip bits
                    ->calcFitness() // Calculate the fitness of all individuals in population
                    ->replaceWeakestIndividual(fittestIndividual) // Replace the weakest individual with the strongest so the max never reduces
                    ->printStats(resultsPath, i + 1, true); // Print the populations fitness stats
        }

        auto best = population->getFitestIndividual();
        best->calcFitness(testData, 400);
        int classified = best->getFitness(testData);
        totalClassified += classified;
        std::cout << "Classification rate for fold " << k << " was " << classified / 400 << "\n";
    }

    std::cout << "Classification rate achieved using " << k + 1 << " fold cross validation ";
    std::cout << "was " << totalClassified / 2000 << "\n";


    return 0;
}
