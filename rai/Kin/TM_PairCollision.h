/*  ------------------------------------------------------------------
    Copyright (c) 2017 Marc Toussaint
    email: marc.toussaint@informatik.uni-stuttgart.de
    
    This code is distributed under the MIT License.
    Please see <root-path>/LICENSE for details.
    --------------------------------------------------------------  */

#pragma once

#include "taskMaps.h"

struct TM_PairCollision : TaskMap {
  int i, j;               ///< which shapes does it refer to?
  bool negScalar=false;
  bool neglectRadii=false;

  TM_PairCollision(int _i, int _j, bool _negScalar, bool _neglectRadii=false);
  TM_PairCollision(const rai::KinematicWorld& K, const char* s1, const char* s2, bool negScalar=false, bool neglectRadii=false);
  virtual void phi(arr& y, arr& J, const rai::KinematicWorld& K);
  virtual uint dim_phi(const rai::KinematicWorld& G){ if(negScalar) return 1;  return 3; }
  virtual rai::String shortTag(const rai::KinematicWorld& G);
};