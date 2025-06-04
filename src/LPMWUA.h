#ifndef LPMWUA_H
#define LPMWUA_H

#include <vector>

#include "weight.h"
#include "LPOutcome.h"
#include "LPOracle.h"
#include "LPReward.h"

// We try to solve min <c, x> s.t. Ax >= b, x >= 0, assuming that c > 0.
class LPMWUA {
public:
  LPMWUA(const std::vector<std::vector<double>> &A, 
         const std::vector<double> &b, const std::vector<double> &c, double opt) : 
    A(A), b(b), c(c), opt(opt), w(A.size(), 1.0), outcome(), oracle(), reward(){}

  void run();
  weights getWeight() { return w; }
  std::vector<std::vector<double>> getOutcomes() { return outcomes; }
  double getRewards() { return cumRewards; }
  bool success() { return suc; }
private:
  const std::vector<std::vector<double>> A;
  const std::vector<double> b;
  const std::vector<double> c;
  double opt;
  std::vector<std::vector<double>> outcomes;
  weights w;
  double cumRewards;
  LPOutcome outcome;
  LPOracle oracle;
  LPReward reward;
  bool suc = true;
};

#endif
