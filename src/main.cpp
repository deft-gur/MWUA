#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "LPMWUA.h"


std::vector<double> solve(std::vector<std::vector<double>> &A, std::vector<double> &b, std::vector<double> &c) {
  double low = 0, high = 10000;

  std::vector<std::vector<double>> outcomes;
  while (high - low > 1e-8) {
    double mid = (high + low)/2;
    std::cout << "low, mid, high: " << low << ' ' << mid << ' ' << high << std::endl;
    LPMWUA MWUA(A, b, c, mid);

    MWUA.run();
    if (!MWUA.success()) {
      low = mid;
      continue;
    }
    outcomes = MWUA.getOutcomes();
    high = mid;
  }

  std::vector<double> res(outcomes[0].size());
  for (auto out : outcomes) {
    std::transform(res.begin(), res.end(), out.begin(), res.begin(), std::plus<>{});
  }
  std::transform(res.begin(), res.end(), res.begin(), [&] (double a) -> double { return a/outcomes.size(); } );

  return res;
}

std::vector<double> matMul(std::vector<std::vector<double>> &A, std::vector<double> &x) {
  std::vector<double> ret(A.size(), 0);
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < x.size(); ++j) {
      ret[i] += A[i][j] * x[j];
    }
  }
  return ret;
}

void printVec(const std::vector<double> &v) {
  for (auto a : v) {
    std::cout << a << ' ';
  }
  std::cout << '\n';
}

std::vector<double> vecAdd(const std::vector<double> &a, const std::vector<double> &b) {
  std::vector<double> v(a.size(), 0);
  for (int i = 0; i < a.size(); ++i) {
    v[i] = a[i] + b[i];
  }
  return v;
}

std::vector<double> vecNeg(const std::vector<double> &a) {
  std::vector<double> v(a.size(), 0);
  for (int i = 0; i < a.size(); ++i) {
    v[i] = -a[i];
  }
  return v;
}

int main() {
  int n = 100, m = 200;
  std::vector<std::vector<double>> A;
  std::vector<double> b;
  A.assign(n, std::vector<double>(m, 0));
  b.assign(n, 0);

  for (int i = 0; i < n; ++i) {
    b[i] = rand() % 5000;
    for (int j = 0; j < m; ++j) {
      A[i][j] = rand() % 5000;
    }
  }
  std::vector<double> c(m, 0);
  for (int i = 0; i < m; ++i) {
    c[i] = (rand() % 3000) + 1;
  }

  std::vector<double> res = solve(A, b, c);

  for (auto a : res) {
    std::cout << a << ' ';
  }
  std::cout << '\n';

  std::cout << "opt val: " << std::inner_product(res.begin(), res.end(), c.begin(), 0.0) << '\n';
  printVec(vecAdd(matMul(A, res), vecNeg(b)));
}
