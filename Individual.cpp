//
// Created by arthur on 29/09/17.
//

#include <random>
#include <functional>
#include <iostream>
#include <chrono>
#include <cstring>
#include "Individual.h"
#include "randomUtil.h"
#include "config.h"

Individual::Individual(int size) {
  this->chromosome = new int[size];
  this->size = size;
  for (int i = 0; i < size; i++) {
    this->chromosome[i] = static_cast<byte>(rand() % 2);
  }
}

void Individual::toString() {
  std::cout << "Chromosome ";
  for (int i = 0; i < this->size; i++) {
    std::cout << unsigned(this->chromosome[i]);
  }
  std::cout << " with fitness " << this->getFitness();
}

void Individual::evaluateFitness() {
}

int Individual::getFitness() {
  this->fitness = 0;
  for (int i = 0; i < this->size; i++) {
    if (this->chromosome[i] == 1) {
      this->fitness++;
    }
  }
  return this->fitness;
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


