#include "LPOutcome.h"

#include <functional>
#include <algorithm>
#include <iostream>

auto makeAddOp(int i, weights& w) -> std::function<double(int, int)> {
  return [&w, i](int a, int b) -> double {
      return a + w.getWeight(i) * b;
  };
}

std::vector<double> LPOutcome::observe(
    const std::vector<std::vector<double>> &A,
    const std::vector<double> &b, const std::vector<double> &c, double opt,
    weights w, LPOracle &oracle) {

  std::vector<double> alpha(A[0].size(), 0);
  double beta = 0;
  for (int i = 0; i < A.size(); ++i) {
    auto f = makeAddOp(i, w);
    std::vector<double> tmp(A[0].size(), 0);
    for (int j = 0; j < alpha.size(); ++j) {
      alpha[j] += A[i][j] * w.getWeight(i);
    }
    //std::transform(alpha.begin(), alpha.end(), A[i].begin(), tmp.begin(), f);
    //alpha = tmp;
    beta += b[i] * w.getWeight(i);
  }


  std::vector<double> ret = oracle.run(c, opt, alpha, beta);
  suc = oracle.getFeasible();

  return ret;
}
