#include "LPOracle.h"
#include <limits>

std::vector<double> LPOracle::run(const std::vector<double> &c, double opt, const std::vector<double> &a, double b) {
  int maxIdx = 0;
  double mx = std::numeric_limits<double>::lowest();
  for (int i = 0; i < a.size(); ++i) {
    if (mx < (a[i] * opt)/c[i]) {
      mx = (a[i]*opt)/c[i];
      maxIdx = i;
    }
  }

  if (a[maxIdx] * opt < b * c[maxIdx]) {
    feasible = false;
    return std::vector<double>();
  }

  std::vector<double> ret(c.size(), 0);
  ret[maxIdx] = opt/c[maxIdx];

  return ret;
}
