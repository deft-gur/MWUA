#include <iostream>
#include <vector>
#include <algorithm>

#include "LPMWUA.h"


void solve(std::vector<std::vector<double>> &A, std::vector<double> &b, std::vector<double> &c) {
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

  for (auto a : res) {
    std::cout << a << ' ';
  }
  std::cout << '\n';
}


int main() {
  std::vector<std::vector<double>> A = {
    {1, 2, 3}, {0, 4, 2}
  };
  std::vector<double> b = {5, 6};
  std::vector<double> c = {1, 2, 1};

  solve(A, b, c);
}
