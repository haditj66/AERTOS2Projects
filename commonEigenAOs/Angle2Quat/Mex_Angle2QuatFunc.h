//
// File: Mex_Angle2QuatFunc.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 21-Jun-2020 14:58:51
//
#ifndef MEX_ANGLE2QUATFUNC_H
#define MEX_ANGLE2QUATFUNC_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "Mex_Angle2QuatFunc_types.h"
//#include <armadillo\src\Geometry\Quaternion.h>

// Function Declarations
//Eigen::Quaternionf Mex_Angle2QuatFunc(double currentYaw, double currentPitch, double currentRoll);
extern void Mex_Angle2QuatFunc(double currentYaw, double currentPitch, double currentRoll, double Q[4]);
extern void Mex_Angle2QuatFunc_initialize();
extern void Mex_Angle2QuatFunc_terminate();

#endif

//
// File trailer for Mex_Angle2QuatFunc.h
//
// [EOF]
//
