//
// Created by arthur on 29/09/17.
//

#include <random>
#include <functional>
#include <iostream>
#include <chrono>
#include <cstring>
#include "Individual.h"

Individual::Individual(int size) {
  this->chromosome = new byte[size];
  this->size = size;

  // Create random number generator using C++ 11 random lib over using rand
  // see https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
  int seed1 = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine gen(seed1);
  std::uniform_int_distribution<int> dist(0, 1);

  for (int i = 0; i < size; i++) {
    this->chromosome[i] = (byte) dist(gen);
  }
}

void Individual::toString() {
  std::cout << "Chromosome ";
  for (int i = 0; i < this->size; i++) {
    std::cout << unsigned(this->chromosome[i]);
  }
  this->evaluateFitness();
  std::cout << " with fitness " << this->fitness;
}

void Individual::evaluateFitness() {
  this->fitness = 0;
  int j = 0;
  for (int i = this->size - 1; i >= 0; i--) {
    if (this->chromosome[i] == 0x01) {
      this->fitness += pow(2, j);
    }
    j++;
  }
}


