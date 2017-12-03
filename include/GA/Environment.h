#ifndef GENETICALGORITHM_ENVIRONMENT_H
#define GENETICALGORITHM_ENVIRONMENT_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Ingester.h>
#include "GA/Config.h"
#include "Population.h"
#include "FPRuleEvaluation.h"

namespace GA {

    template <typename fitnessType>
    class Environment {

    public:

        Environment(Config* conf, RulesEngine* rulesEngine, IEvaluation<fitnessType>* evaluation, IMutatable<fitnessType>* mutator) {
            this->conf = conf;
            this->rulesEngine = rulesEngine;
            this->evaluation = evaluation;
            this->mutator = mutator;
        }

        Individual<fitnessType>* run() {

            /* initialize random seed: */
            srand (time(NULL));

            // Create results file to save fitness values to
            std::string resultsPath;
            if (!conf->resultsFile.compare("")) {
                try {
                    resultsPath = createResultsFile(conf);
                } catch(const char* err) {
                    std::cout << err << "\n";
                    return NULL;
                }
            }

            int totalClassified = 0;

            int k;
            for (k = 0; k < conf->NUMBER_OF_FOLDS; k++) {

                std::ostringstream ssTrainPath;
                ssTrainPath << "../data/fold" << k + 1 << "/train.txt";

                std::ostringstream ssTestPath;
                ssTestPath << "../data/fold" << k + 1 << "/test.txt";
                std::string path = ssTestPath.str();

                auto ingester = new Ingester(conf->NUMBER_OF_DATA, conf->DATA_LENGTH);
                auto trainData = ingester->readFile(ssTrainPath.str().c_str());
                auto testData = ingester->readFile(ssTestPath.str().c_str());

                // Create main population that we will be generating
                auto population = new Population<unsigned long>(trainData, evaluation, conf, mutator);

                Individual<unsigned long>* fittestIndividual;

                // Seed the first population randomly
                population->generate(conf->SIZE_OF_POPULATION);

                // Loop over the number of generations and evolve the GA
                for (int i = 0; i < conf->NUMBER_OF_GENERATIONS; i++) {
                    fittestIndividual = population->cloneFittestIndividual();

                    population = population->selectParents(); // First, let's perform tournament selection and create a new population of the fittest
                    population->crossover(); // Now, pair the individuals and perform crossover
                    population->mutate(); // Once crossover is done, run mutation to randomly flip bits
                    population->calcFitness(); // Calculate the fitness of all individuals in population
                    population->replaceWeakestIndividual(fittestIndividual); // Replace the weakest individual with the strongest so the max never reduces
                    population->printStats(resultsPath, i + 1, true); // Print the populations fitness stats
                }

                auto best = population->getFitestIndividual();
                int classified = evaluation->calculateFitness(best, testData);
                totalClassified += classified;
                std::cout << "Classification rate for fold " << k << " was " << classified / 400 << "\n";
            }

            std::cout << "Classification rate achieved using " << k + 1 << " fold cross validation ";
            std::cout << "was " << totalClassified / 2000 << "\n";

        }

    private:
        struct Config* conf;
        RulesEngine* rulesEngine;
        IEvaluation<fitnessType>* evaluation;
        IMutatable<fitnessType>* mutator;

    };

}


#endif //GENETICALGORITHM_ENVIRONMENT_H
