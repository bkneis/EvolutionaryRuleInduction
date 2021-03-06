#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>
#include "Individual.h"
#include "IEvaluation.h"
#include "IMutatable.h"

namespace GA {

    template <typename fitnessType = int>
    class Population {

    public:

        Population(data* dataIn) {
            this->dataIn = dataIn;
        }

        Population(data* dataIn, IEvaluation<fitnessType>* evaluation, Config* conf, IMutatable<fitnessType>* mutator) {
            this->dataIn = dataIn;
            this->evaluation = evaluation;
            this->conf = conf;
            this->mutator = mutator;
        }

        std::vector<Individual<fitnessType>*> individuals;

        void generate(int size) {
            for (int i = 0; i < size; i++) {
                this->individuals.push_back(new Individual<fitnessType>(conf->NUMBER_OF_CHROMOSOMES, RULES, conf));
            }
            this->calcFitness();
        }

        void toString() {
            for (int i = 0; i < this->individuals.size(); i++) {
                std::cout << "Individual at index " << i << " has ";
                this->individuals.at(i)->toString(true);
                std::cout << "\n";
            }
        }

        Population* selectParents() {
            auto tempPopulation = new Population<fitnessType>(this->dataIn, this->evaluation, conf, mutator);

            for (int i = 0; i < conf->SIZE_OF_POPULATION; i++) {

                std::vector<Individual<fitnessType>*> tournament;

                for (int j = 0; j < conf->TOURNAMENT_SIZE; j++) {
                    tournament.push_back(this->individuals.at(getRandomNumber<unsigned long> (0, conf->SIZE_OF_POPULATION - 1)));
                }

                auto clonedParent = new Individual<unsigned long>(conf->NUMBER_OF_CHROMOSOMES, RULES, conf);
                auto parentChromosomes = new float[conf->NUMBER_OF_CHROMOSOMES];

                auto best = tournament.at(0);

                for (auto parent: tournament) {
                    if (parent->getFitness(this->dataIn) > best->getFitness(this->dataIn)) {
                        best = parent;
                    }
                }

                memcpy(parentChromosomes, best->getChromosomes(), conf->NUMBER_OF_CHROMOSOMES * sizeof(float));

                clonedParent->setChromosomes(parentChromosomes);
                tempPopulation->addIndividual(clonedParent);
            }
            return tempPopulation;
        }

        Population* mutate() {
            for (auto &individual: this->individuals) {
                mutator->mutate(individual, conf);
            }
            return this;
        }

        Population* crossover() {
            for (unsigned long i = 0; i < this->individuals.size() - 2; i += 2) {
                if (getRandomNumber(1, 100) <= conf->PROBABILITY_OF_CROSSOVER) {
                    auto parent1 = this->individuals.at(i);
                    auto parent2 = this->individuals.at(i + 1);
                    parent1->crossover(parent2);
                }
            }
            return this;
        }

        Population* printStats(std::string path, int generation, bool printBest = false) {
            this->calcStats();

            std::cout << "Generation: " << generation << "\n";

            std::ofstream resultsFile;
            resultsFile.open(path, std::ios_base::app);

            if (resultsFile.is_open()) {
                resultsFile << this->getMaxFitness() << "," << this->getMeanFitness() << "\n";
            } else {
                std::cout << "Could not write to the results file \n";
            }
            if (printBest) {
                std::cout << "The mean fitness for the population is " << this->getMeanFitness() << "\n";
                std::cout << "The best individual in the population has fitness " << this->getMaxFitness() << "\n";
                std::cout << "The best individual's chromosome is \n";
                auto best = this->getFitestIndividual()->getChromosomes();
                for (int i = 0; i < conf->NUMBER_OF_CHROMOSOMES; i++) {
                    if ((i + 1) % (conf->DATA_LENGTH * 2 + 1) == 0) {
                        std::cout << " = ";
                        // resultsFile << " = ";
                    }
                    std::cout << best[i] << " ";
                    // resultsFile << best[i] << " ";
                    if ((i + 1) % (conf->DATA_LENGTH * 2 + 1) == 0) {
                        std::cout << "\n";
                        // resultsFile << "\n";
                    }
                }
                std::cout << "\n";
                // resultsFile << "\n";
            }
            resultsFile.close();
            return this;
        }

        int getMaxFitness() {
            return this->maxFitness;
        }

        int getMeanFitness() {
            return this->meanFitness;
        }

        void addIndividual(Individual<fitnessType>* individual) {
            this->individuals.push_back(individual);
        }

        Population* calcFitness() {
            for (unsigned long i = 0; i < this->individuals.size(); i++) {
                auto individual = this->individuals.at(i);
                int fitness = evaluation->calculateFitness(individual, this->dataIn);
                individual->setFitness(fitness);
                // individual->calcFitness(this->dataIn);
            }
            return this;
        }

        Population* calcStats() {
            int total = 0;
            int fitness;
            this->maxFitness = 0;
            for (auto &individual : this->individuals) {
                fitness = individual->getFitness(this->dataIn);
                if (fitness > this->maxFitness) {
                    this->maxFitness = fitness;
                }
                total += fitness;
            }
            this->meanFitness = static_cast<fitnessType>(total / this->individuals.size());
            return this;
        }

        Individual<fitnessType>* getFitestIndividual() {
            auto fittest = this->individuals.at(0);
            int fitness;
            for (auto individual : this->individuals) {
                fitness = individual->getFitness(this->dataIn);
                if (fitness > fittest->getFitness(this->dataIn)) {
                    fittest = individual;
                }
            }
            return fittest;
        }

        Population* replaceWeakestIndividual(Individual<fitnessType>* fittest) {
            unsigned long weakest = 0;
            int fitness;
            for (unsigned long i = 0; i < this->individuals.size(); i++) {
                fitness = this->individuals.at(i)->getFitness(this->dataIn);
                if (fitness < this->individuals.at(weakest)->getFitness(this->dataIn)) {
                    weakest = i;
                }
            }
            auto weak = this->individuals.at(weakest);
            auto it = this->individuals.begin() + weakest;
            it = this->individuals.erase(it);
            this->individuals.insert(it, fittest);
            return this;
        }

        Individual<fitnessType>* cloneFittestIndividual() {
            auto fittestIndividual = this->getFitestIndividual();
            int size = fittestIndividual->getSize();
            auto fittestChromosomes = new float[size];
            int fitness = fittestIndividual->getFitness(this->dataIn);
            memcpy(fittestChromosomes, fittestIndividual->getChromosomes(), size * sizeof(float));
            fittestIndividual = new Individual<fitnessType> (size, fittestIndividual->getFitnessStrategy(), conf);
            fittestIndividual->setChromosomes(fittestChromosomes);
            fittestIndividual->setFitness(fitness);
            return fittestIndividual;
        }

    private:

        int maxFitness;
        int meanFitness;
        data* dataIn;
        IEvaluation<fitnessType>* evaluation;
        Config* conf;
        IMutatable<fitnessType>* mutator;

    };

}

#endif //GENETICALGORITHM_POPULATION_H
