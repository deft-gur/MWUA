#include <random>
#include <assert.h>
#include <iostream>

#include "weight.h"

weights::weights(int n, double weight) : n(n), sum(weight*n) {
  w.assign(n, weight);
}

double weights::getWeight(int i) {
  return w[i];
}

double weights::getSum() { return sum; }

int weights::size() { return n; }

int weights::draw() {
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, getSum());
  int choice = distribution(generator);
  int idx = 0;
  for (auto a : w) {
    choice -= a;
    if (choice <= 0) return idx;
    idx++;
  }

  assert(false);
}

void weights::updateWeight(int i, double newWeight) {
  sum = sum - w[i] + newWeight;
  w[i] = newWeight;
}

void weights::addWeight(int i, double add) {
  sum += add;
  w[i] += add;
}

void weights::mulWeight(int i, double reward) {
  sum -= w[i];
  // TODO: 0.1 is the learning rate for now.
  double eps = 0.1;
  if (reward >= 0) {
    w[i] = w[i] * pow(1.0 + eps, reward/100);
  } else {
    w[i] = w[i] * pow(1.0 - eps, -reward/100);
  }
  sum += w[i];
}
