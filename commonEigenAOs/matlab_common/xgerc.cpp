//
// File: xgerc.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 17-Jun-2020 10:37:31
//

// Include Files
#include "xgerc.h"
#include "ellipsoid_fit.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : int m
//                int n
//                double alpha1
//                int ix0
//                const double y[3]
//                double A[9]
//                int ia0
// Return Type  : void
//
void xgerc(int m, int n, double alpha1, int ix0, const double y[3], double A[9],
           int ia0)
{
  int jA;
  if (!(alpha1 == 0.0)) {
    int jy;
    jA = ia0;
    jy = 0;
    for (int j = 0; j < n; j++) {
      if (y[jy] != 0.0) {
        double temp;
        int ix;
        int i;
        temp = y[jy] * alpha1;
        ix = ix0;
        i = m + jA;
        for (int ijA = jA; ijA < i; ijA++) {
          A[ijA - 1] += A[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += 3;
    }
  }
}

//
// File trailer for xgerc.cpp
//
// [EOF]
//
