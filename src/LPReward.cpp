#include <numeric>
#include "LPReward.h"


double LPReward::reward(const std::vector<std::vector<double>> &A,
                const std::vector<double> &b, int idx,
                const std::vector<double> &v){

  return b[idx] - std::inner_product(A[idx].begin(),A[idx].end(), v.begin(), 0.0);
}
