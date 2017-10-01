//
// Created by arthur on 29/09/17.
//

#include <iostream>
#include "Population.h"
#include "Individual.h"

void Population::generate(int size) {
    for (int i = 0; i < size; i++) {
        this->individuals.push_back(new Individual(4));
    }
}

Population::Population(int size) {
    this->generate(size);
}

void Population::getMaxFitness() {

}

void Population::toString() {
    for (int i = 0; i < this->individuals.size(); i++) {
        std::cout << "Individual at index " << i << " has ";
        this->individuals.at(i)->toString();
        std::cout << "\n";
    }
}
