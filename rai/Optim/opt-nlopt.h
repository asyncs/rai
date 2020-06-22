#include <Optim/MathematicalProgram.h>
#include <nlopt.hpp>

struct NLOptInterface {
  MathematicalProgram& P;
  arr x, phi_x, J_x;
  ObjectiveTypeA featureTypes;

  NLOptInterface(MathematicalProgram& _P) : P(_P) {
    P.getFeatureTypes(featureTypes);
  }

  void solve();

private:
  double f(const std::vector<double> &_x, std::vector<double> &_grad);
  double g(const std::vector<double> &_x, std::vector<double> &_grad, uint feature);
  double h(const std::vector<double> &_x, std::vector<double> &_grad, uint feature);

  static double _f(const std::vector<double> &x, std::vector<double> &grad, void* f_data);
  static double _g(const std::vector<double> &x, std::vector<double> &grad, void* f_data);
  static double _h(const std::vector<double> &x, std::vector<double> &grad, void* f_data);
};
