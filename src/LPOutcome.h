#ifndef LPOUTCOME_H
#define LPOUTCOME_H

#include <vector>
#include "weight.h"
#include "LPOracle.h"

class LPOutcome {
public:
  std::vector<double> observe(
      const std::vector<std::vector<double>> &A,
      const std::vector<double> &b, const std::vector<double> &c, double opt,
      weights w, LPOracle &oracle);
  bool success() { return suc; }
private:
  bool suc = true;
};

#endif
