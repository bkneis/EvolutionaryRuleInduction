#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>
#include "Individual.h"

template <typename fitnessType = int>
class Population {

public:

    std::vector<Individual<fitnessType>*> individuals;

    void generate(int size) {
        for (int i = 0; i < size; i++) {
            this->individuals.push_back(new Individual<fitnessType>(NUMBER_OF_CHROMOSONES, RULES));
        }
    }

    void toString() {
        for (int i = 0; i < this->individuals.size(); i++) {
            std::cout << "Individual at index " << i << " has ";
            this->individuals.at(i)->toString();
            std::cout << "\n";
        }
    }

    Population* selectParents() {
        auto tempPopulation = new Population<fitnessType>();

        for (int i = 0; i < SIZE_OF_POPULATION; i++) {
            auto parent1 = this->individuals.at(getRandomNumber<unsigned long> (0, SIZE_OF_POPULATION - 1));
            auto parent2 = this->individuals.at(getRandomNumber<unsigned long> (0, SIZE_OF_POPULATION - 1));

            if (parent1->getFitness() >= parent2->getFitness()) {
                tempPopulation->addIndividual(parent1);
            } else {
                tempPopulation->addIndividual(parent2);
            }
        }
        return tempPopulation;
    }

    Population* mutate() {
        for (unsigned long i = 0; i < this->individuals.size() - 1; i++) {
            if (getRandomNumber(1, 100) <= PROBABILITY_OF_MUTATION) {
                auto individual = this->individuals.at(i);
                individual->mutate();
            }
        }
        return this;
    }

    Population* crossover() {
        for (unsigned long i = 0; i < this->individuals.size() - 2; i += 2) {
            if (getRandomNumber(1, 100) <= PROBABILITY_OF_CROSSOVER) {
                auto parent1 = this->individuals.at(i);
                auto parent2 = this->individuals.at(i + 1);
                parent1->crossover(parent2);
            }
        }
        return this;
    }

    Population* printStats(std::string path) {
        this->calcStats();

        std::ofstream resultsFile;
        resultsFile.open(path, std::ios_base::app);

        if (resultsFile.is_open()) {
            resultsFile << this->getMaxFitness() << "," << this->getMeanFitness() << "\n";
            resultsFile.close();
        } else {
            std::cout << "Could not write to the results file \n";
        }
        std::cout << "The best individual in the population has fitness " << this->getMaxFitness() << "\n";
        std::cout << "The mean fitness for the population is " << this->getMeanFitness() << "\n";
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

    Population* calcStats() {
        int total = 0;
        int fitness;
        this->maxFitness = 0;
        for (auto &individual : this->individuals) {
            fitness = individual->getFitness();
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
            fitness = individual->getFitness();
            if (fitness > fittest->getFitness()) {
                fittest = individual;
            }
        }
        return fittest;
    }

    Population* replaceWeakestIndividual(Individual<fitnessType>* fittest) {
        unsigned long weakest = 0;
        int fitness;
        for (unsigned long i = 0; i < this->individuals.size(); i++) {
            fitness = this->individuals.at(i)->getFitness();
            if (fitness < this->individuals.at(weakest)->getFitness()) {
                weakest = i;
            }
        }
        this->individuals.insert(this->individuals.begin() + weakest, fittest);
    }

    Individual<fitnessType>* cloneFittestIndividual() {
        auto fittestIndividual = this->getFitestIndividual();
        int size = fittestIndividual->getSize();
        auto fittestChromosomes = new int[size];
        memcpy(fittestChromosomes, fittestIndividual->getChromosomes(), size * sizeof(int));
        fittestIndividual = new Individual<fitnessType> (size, fittestIndividual->getFitnessStrategy());
        fittestIndividual->setChromosomes(fittestChromosomes);
        return fittestIndividual;
    }

private:

    int maxFitness;
    int meanFitness;
};

#endif //GENETICALGORITHM_POPULATION_H
