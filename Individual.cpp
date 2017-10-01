//
// Created by arthur on 29/09/17.
//

#include <random>
#include <functional>
#include <iostream>
#include <chrono>
#include "Individual.h"

Individual::Individual(int size) {
  this->chromosome = new uint8_t[size];
  this->size = size;

  // Create random number generator using C++ 11 random lib over using rand
  // see https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
  int seed1 = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine gen(seed1);
  std::uniform_int_distribution<int> dist(0, 1);

  for (int i = 0; i < size; i++) {
    this->chromosome[i] = (uint8_t ) (dist(gen));
  }
}

void Individual::toString() {
  std::cout << "Chromosome ";
  for (int i = 0; i < this->size; i++) {
    std::cout << unsigned(this->chromosome[i]);
  }
}

void Individual::evaluateFitness() {

}
