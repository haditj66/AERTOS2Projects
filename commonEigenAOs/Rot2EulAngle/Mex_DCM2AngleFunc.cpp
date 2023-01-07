//
// File: Mex_DCM2AngleFunc.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 19-Jun-2020 18:30:18
//

// Include Files
#include "Mex_DCM2AngleFunc.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Variable Definitions
static boolean_T isInitialized_Rot2Angle = false;

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int b_u0;
    int b_u1;
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

//
// Arguments    : const double DCM__[9]
//                double *Yaw
//                double *Pitch
//                double *Roll
// Return Type  : void
//
void Mex_DCM2AngleFunc(const double DCM__[9], float *Yaw, float *Pitch, float
  *Roll)
{
  double sy;
  double eulShaped_idx_0;
  double eulShaped_idx_1;
  double eulShaped_idx_2;
  double y_data[1];
  double varargin_1_data[1];
  double varargin_2_data[1];
  if (!isInitialized_Rot2Angle) {
    Mex_DCM2AngleFunc_initialize();
  }

  sy = std::sqrt(DCM__[8] * DCM__[8] + DCM__[7] * DCM__[7]);
  eulShaped_idx_0 = rt_atan2d_snf(DCM__[3], DCM__[0]);
  eulShaped_idx_1 = rt_atan2d_snf(-DCM__[6], sy);
  eulShaped_idx_2 = rt_atan2d_snf(DCM__[7], DCM__[8]);
  if (sy < 2.2204460492503131E-15) {
    int i;
    y_data[0] = -DCM__[1];
    varargin_1_data[0] = rt_atan2d_snf(y_data[0], DCM__[4]);
    y_data[0] = -DCM__[6];
    varargin_2_data[0] = rt_atan2d_snf(y_data[0], sy);
    for (i = 0; i < 1; i++) {
      eulShaped_idx_0 = varargin_1_data[0];
    }

    for (i = 0; i < 1; i++) {
      eulShaped_idx_1 = varargin_2_data[0];
    }

    eulShaped_idx_2 = 0.0;
  }

  eulShaped_idx_0 = -eulShaped_idx_0;
  eulShaped_idx_1 = -eulShaped_idx_1;
  eulShaped_idx_2 = -eulShaped_idx_2;
  *Yaw = (float)-eulShaped_idx_0;
  *Pitch = (float)-eulShaped_idx_1;
  *Roll = (float) -eulShaped_idx_2;
}

//
// Arguments    : void
// Return Type  : void
//
void Mex_DCM2AngleFunc_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_Rot2Angle = true;
}

//
// Arguments    : void
// Return Type  : void
//
void Mex_DCM2AngleFunc_terminate()
{
  // (no terminate code required)
  isInitialized_Rot2Angle = false;
}

//
// File trailer for Mex_DCM2AngleFunc.cpp
//
// [EOF]
//
