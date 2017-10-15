#include <functional>
#include <iostream>
#include <chrono>
#include <cstring>
#include <cmath>
#include "Individual.h"
#include "randomUtil.h"
#include "config.h"

Individual::Individual(int size, fitnessStrategy strategy) {
  this->chromosome = new int[size];
  this->fitnessStrat = strategy;
  this->size = size;
  for (int i = 0; i < size; i++) {
    this->chromosome[i] = getRandomNumber(0, 1);
  }
}

void Individual::toString() {
  std::cout << "Chromosome ";
  for (int i = 0; i < this->size; i++) {
    std::cout << unsigned(this->chromosome[i]);
  }
  std::cout << " with fitness " << this->getFitness();
}

int Individual::getFitness() {
  switch (this->fitnessStrat) {
    case (COUNTING_ONES):
      return this->getFitnessCountingOnes();
    case (SQUARED):
      return this->getFitnessSquared();
    default:
      std::cout << "Please choose an appropriate fitness strategy"; return 0;
  }
}

int Individual::getSize() {
  return this->size;
}

void Individual::crossover(Individual* partner) {
  int point = getRandomNumber(0, NUMBER_OF_CHROMOSONES);
  auto partnerChromosomes = partner->getChromosomes();
  int tempBit;
  for (int i = point; i < this->size; i++) {
    tempBit = this->chromosome[i];
    this->chromosome[i] = partnerChromosomes[i];
    partnerChromosomes[i] = tempBit;
  }
  partner->setChromosomes(partnerChromosomes);
}

void Individual::mutate() {
  int point = getRandomNumber(0, NUMBER_OF_CHROMOSONES);
  this->chromosome[point] = 1 - this->chromosome[point];
}

int* Individual::getChromosomes() {
  return this->chromosome;
}

int* Individual::setChromosomes(int* chromosome) {
  this->chromosome = chromosome;
}

int Individual::getFitnessSquared() {
  this->fitness = 0;
  for (int i = 0; i < this->size; i++) {
    if (this->chromosome[i] == 1) {
      this->fitness += pow(2, i);
    }
  }
  return this->fitness;
}

int Individual::getFitnessCountingOnes() {
  this->fitness = 0;
  for (int i = 0; i < this->size; i++) {
    if (this->chromosome[i] == 1) {
      this->fitness++;
    }
  }
  return this->fitness;
}

fitnessStrategy Individual::getFitnessStrategy() {
    return this->fitnessStrat;
}


