#ifndef LPORACLE_H
#define LPORACLE_H

#include <vector>

// We solve a very special class of LP programs where we assume that c > 0, our
// feasible region is P := { x >= 0 : <c,x> = opt}, and we wish to find an x such
// that <a,x> >= b with x >= 0.
class LPOracle{
public:
  LPOracle() : feasible(true) {}

  // run(a,b) returns a feasible solution if one exists. If no solution exists
  // then it will return an empty vector.
  std::vector<double> run(const std::vector<double> &c, double opt, const std::vector<double> &a, double b);
  // You should check if the solution is feasible after calling run(a,b).
  bool getFeasible() { return feasible; }
private:
  bool feasible;
};

#endif
