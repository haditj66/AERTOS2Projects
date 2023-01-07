//
// File: ellipsoid_fit_initialize.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 17-Jun-2020 10:37:31
//

// Include Files
#include "ellipsoid_fit_initialize.h"
#include "ellipsoid_fit.h"
#include "ellipsoid_fit_data.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void ellipsoid_fit_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_ellipsoid_fit = true;
}

//
// File trailer for ellipsoid_fit_initialize.cpp
//
// [EOF]
//
