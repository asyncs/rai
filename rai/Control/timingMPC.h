#pragma once

#include "../Core/array.h"
#include "../Optim/options.h"
#include "../Algo/spline.h"

struct SolverReturn;

//A wrapper of TimingOpt optimize the timing (and vels) along given waypoints, and progressing/backtracking the phase
struct TimingMPC{
  arr waypoints;
  arr tangents;
  arr vels;
  arr tau;
  arr warmstart_dual;

  //optimization parameters
  double timeCost;
  double ctrlCost;
  rai::OptOptions opt;

  //tangent options
  bool useNextWaypointTangent=true;

  //phase management
  uint phase=0;
  uintA backtrackingTable;

  TimingMPC(const arr& _waypoints, double _timeCost=1e0, double _ctrlCost=1e0);

  shared_ptr<SolverReturn> solve(const arr& x0, const arr& v0, int verbose=1);

  bool done() const{ return phase>=waypoints.d0; }
  arr getWaypoints() const{ if(done()) return arr{}; return waypoints({phase, -1}).copy(); }
  arr getTimes() const{ if(done()) return arr{}; return integral(tau({phase, -1})); }
  arr getVels() const;

  void update_progressTime(double gap);
  void update_waypoints(const arr& _waypoints, bool setNextWaypointTangent);
  void update_backtrack();
  void update_setPhase(uint phaseTo);

  void getCubicSpline(rai::CubicSpline& S, const arr& x0, const arr& v0) const;
};
