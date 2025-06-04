#include <iostream>

#include "LPMWUA.h"

void LPMWUA::run() {
  cumRewards = 0;
  int NumRounds = 1000;
  outcomes.assign(0, std::vector<double>());

  for (int t = 0; t < NumRounds; ++t) {
    int Idx = w.draw();
    std::vector<double> x = outcome.observe(A, b, c, opt, w, oracle);
    suc = outcome.success();
    if (!outcome.success()) {
      return;
    }
    outcomes.push_back(x);
    double curReward = reward.reward(A, b, Idx, x);
    cumRewards += curReward;

    bool cont = true;
    for (int i = 0; i < w.size(); ++i) {
      w.mulWeight(i, reward.reward(A, b, i, x));
      cont = cont && (w.getWeight(i) > 1e-6);
    }
    if (!cont) return;
  }
}

