#ifndef LPREWARD_H
#define LPREWARD_H

#include <vector>

class LPReward{
public:
  LPReward() {}

  double reward(const std::vector<std::vector<double>> &A,
                const std::vector<double> &b, int idx,
                const std::vector<double> &v);
};

#endif
