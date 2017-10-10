#include <iostream>
#include "Population.h"
#include "config.h"
#include "randomUtil.h"

void Population::generate(int size) {
    for (int i = 0; i < size; i++) {
        this->individuals.push_back(new Individual(NUMBER_OF_CHROMOSONES));
    }
}

void Population::toString() {
    for (int i = 0; i < this->individuals.size(); i++) {
        std::cout << "Individual at index " << i << " has ";
        this->individuals.at(i)->toString();
        std::cout << "\n";
    }
}

Population* Population::selectParents() {
    auto tempPopulation = new Population();

    for (int i = 0; i < SIZE_OF_POPULATION; i++) {
        auto parent1 = this->individuals.at(static_cast<unsigned long>(getRandomNumber(0, SIZE_OF_POPULATION - 1)));
        auto parent2 = this->individuals.at(static_cast<unsigned long>(getRandomNumber(0, SIZE_OF_POPULATION - 1)));

        if (parent1->getFitness() >= parent2->getFitness()) {
            tempPopulation->addIndividual(parent1);
        } else {
            tempPopulation->addIndividual(parent2);
        }
    }
    return tempPopulation;
}

Population *Population::mutate() {
    for (int i = 0; i < this->individuals.size() - 1; i++) {
        if (getRandomNumber(1, 100) <= PROBABILITY_OF_MUTATION) {
            auto individual = this->individuals.at(static_cast<unsigned long>(i));
            individual->mutate();
        }
    }
    return this;
}

Population *Population::crossover() {
    for (int i = 0; i < this->individuals.size() - 2; i += 2) {
        if (getRandomNumber(1, 100) <= PROBABILITY_OF_CROSSOVER) {
            auto parent1 = this->individuals.at(static_cast<unsigned long>(i));
            auto parent2 = this->individuals.at(static_cast<unsigned long>(i + 1));
            parent1->crossover(parent2);
        }
    }
    return this;
}

Population *Population::printStats() {
    this->calcStats();
    std::cout << "The best individual in the population has fitness " << this->getMaxFitness() << "\n";
    std::cout << "The mean fitness for the population is " << this->getMeanFitness() << "\n";
    return this;
}

int Population::getMaxFitness() {
    return this->maxFitness;
}

int Population::getMeanFitness() {
    return this->meanFitness;
}

void Population::addIndividual(Individual* individual) {
    this->individuals.push_back(individual);
}

Population* Population::calcStats() {
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
    this->meanFitness = static_cast<int>(total / this->individuals.size());
    return this;
}

Individual *Population::getFitestIndividual() {
    auto fittest = this->individuals.at(0);
    int fitness;
    for (auto &individual : this->individuals) {
        fitness = individual->getFitness();
        if (fitness > fittest->getFitness()) {
            fittest = individual;
        }
    }
    return fittest;
}

Population* Population::replaceWeakestIndividual(Individual* fittest) {
    unsigned long weakest = 0;
    int fitness;
    for (unsigned long i = 0; i < this->individuals.size(); i++) {
        fitness = this->individuals.at(i)->getFitness();
        if (fitness < this->individuals.at(weakest)->getFitness()) {
            weakest = i;
        }
    }
    this->individuals.at(weakest) = fittest;
}
