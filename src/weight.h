#ifndef WEIGHT_H
#define WEIGHT_H

#include <vector>

class weights {
public:
  weights(int n, double weight = 1.0);

  double getWeight(int i);
  double getSum();
  int size();
  int draw();
  void updateWeight(int i, double newWeight);
  void addWeight(int i, double add);
  void mulWeight(int i, double reward);
private:
  std::size_t n;
  int sum;
  std::vector<double> w;
};

#endif
