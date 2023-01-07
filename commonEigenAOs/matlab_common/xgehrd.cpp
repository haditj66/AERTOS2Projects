//
// File: xgehrd.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 17-Jun-2020 10:37:31
//

// Include Files
#include "xgehrd.h"
#include "ellipsoid_fit.h"
#include "ellipsoid_fit_rtwutil.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xgerc.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : double a[9]
//                double tau[2]
// Return Type  : void
//
void xgehrd(double a[9], double tau[2])
{
  double work[3];
  double alpha1;
  double xnorm;
  double beta1;
  int lastv;
  int lastc;
  int knt;
  int jy;
  boolean_T exitg2;
  int ix;
  int i;
  int ia;
  int exitg1;
  int i1;
  work[0] = 0.0;
  work[1] = 0.0;
  work[2] = 0.0;
  alpha1 = a[1];
  tau[0] = 0.0;
  xnorm = std::abs(a[2]);
  if (xnorm != 0.0) {
    beta1 = rt_hypotd_snf(a[1], xnorm);
    if (a[1] >= 0.0) {
      beta1 = -beta1;
    }

    if (std::abs(beta1) < 1.0020841800044864E-292) {
      knt = -1;
      do {
        knt++;
        for (jy = 3; jy < 4; jy++) {
          a[2] *= 9.9792015476736E+291;
        }

        beta1 *= 9.9792015476736E+291;
        alpha1 *= 9.9792015476736E+291;
      } while (!(std::abs(beta1) >= 1.0020841800044864E-292));

      beta1 = rt_hypotd_snf(alpha1, std::abs(a[2]));
      if (alpha1 >= 0.0) {
        beta1 = -beta1;
      }

      tau[0] = (beta1 - alpha1) / beta1;
      xnorm = 1.0 / (alpha1 - beta1);
      for (jy = 3; jy < 4; jy++) {
        a[2] *= xnorm;
      }

      for (jy = 0; jy <= knt; jy++) {
        beta1 *= 1.0020841800044864E-292;
      }

      alpha1 = beta1;
    } else {
      tau[0] = (beta1 - a[1]) / beta1;
      xnorm = 1.0 / (a[1] - beta1);
      for (jy = 3; jy < 4; jy++) {
        a[2] *= xnorm;
      }

      alpha1 = beta1;
    }
  }

  a[1] = 1.0;
  if (tau[0] != 0.0) {
    lastv = 1;
    knt = 2;
    while ((lastv + 1 > 0) && (a[knt] == 0.0)) {
      lastv--;
      knt--;
    }

    lastc = 3;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      knt = lastc + 3;
      ia = knt;
      do {
        exitg1 = 0;
        if (ia <= knt + lastv * 3) {
          if (a[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia += 3;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = -1;
    lastc = 0;
  }

  if (lastv + 1 > 0) {
    if (lastc != 0) {
      if (0 <= lastc - 1) {
        std::memset(&work[0], 0, lastc * sizeof(double));
      }

      ix = 1;
      i = 3 * lastv + 4;
      for (jy = 4; jy <= i; jy += 3) {
        knt = 0;
        i1 = (jy + lastc) - 1;
        for (ia = jy; ia <= i1; ia++) {
          work[knt] += a[ia - 1] * a[ix];
          knt++;
        }

        ix++;
      }
    }

    if (!(-tau[0] == 0.0)) {
      knt = 3;
      jy = 1;
      for (ia = 0; ia <= lastv; ia++) {
        if (a[jy] != 0.0) {
          xnorm = a[jy] * -tau[0];
          ix = 0;
          i = knt + 1;
          i1 = lastc + knt;
          for (int ijA = i; ijA <= i1; ijA++) {
            a[ijA - 1] += work[ix] * xnorm;
            ix++;
          }
        }

        jy++;
        knt += 3;
      }
    }
  }

  if (tau[0] != 0.0) {
    lastv = 2;
    knt = 2;
    while ((lastv > 0) && (a[knt] == 0.0)) {
      lastv--;
      knt--;
    }

    lastc = 2;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      knt = (lastc - 1) * 3 + 5;
      ia = knt;
      do {
        exitg1 = 0;
        if (ia <= (knt + lastv) - 1) {
          if (a[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      if (0 <= lastc - 1) {
        std::memset(&work[0], 0, lastc * sizeof(double));
      }

      knt = 0;
      i = 3 * (lastc - 1) + 5;
      for (jy = 5; jy <= i; jy += 3) {
        ix = 2;
        xnorm = 0.0;
        i1 = (jy + lastv) - 1;
        for (ia = jy; ia <= i1; ia++) {
          xnorm += a[ia - 1] * a[ix - 1];
          ix++;
        }

        work[knt] += xnorm;
        knt++;
      }
    }

    xgerc(lastv, lastc, -tau[0], 2, work, a, 5);
  }

  a[1] = alpha1;
  alpha1 = a[5];
  tau[1] = 0.0;
  a[5] = 1.0;
  a[5] = alpha1;
}

//
// File trailer for xgehrd.cpp
//
// [EOF]
//
