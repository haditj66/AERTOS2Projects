//
// File: ellipsoid_fit.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 17-Jun-2020 10:37:31
//

// Include Files
#include "ellipsoid_fit.h"
#include "eig.h"
#include "ellipsoid_fit_data.h"
#include "ellipsoid_fit_initialize.h"
#include "mldivide.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include <cmath>

// Function Definitions

//
// Fit an (non)rotated ellipsoid or sphere to a set of xyz data points
//  XYZ: N(rows) x 3(cols), matrix of N data points (x,y,z)
//  optional flag f, default to 0 (fitting of rotated ellipsoid)
// Arguments    : const double XYZ[4803]
//                double ofs[3]
//                creal_T gain[3]
//                creal_T rotM[9]
// Return Type  : void
//
void ellipsoid_fit(double *XYZ, double ofs[3], creal_T gain[3],
                   creal_T rotM[9])
{
  int r3;
  double maxval;
  double a21;
  double y_tmp[81];
  double v[9];
  double brm;
  int r1;
  static float D[14409];
  double A[16];
  static float b_y_tmp[14409];
  int r2;
  double B[3];
  double b_A[9];
  double Tmtx[16];
  static const signed char iv[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 1 };

  double b_Tmtx[16];
  creal_T ev[9];
  if (!isInitialized_ellipsoid_fit) {
    ellipsoid_fit_initialize();
  }

  //  any axes (rotated ellipsoid)
  for (r3 = 0; r3 < 1601; r3++) {
    double D_tmp;
    maxval = 2.0 * XYZ[r3];
    a21 = (XYZ[r3 + 1601]);
    brm = 2.0 * a21;
    D[r3] = (XYZ[r3]) * (XYZ[r3]);
    D[r3 + 1601] = a21 * a21;
    D_tmp = (XYZ[r3 + 3202]);
    D[r3 + 3202] = D_tmp * D_tmp;
    D[r3 + 4803] = maxval * a21;
    D[r3 + 6404] = maxval * D_tmp;
    D[r3 + 8005] = brm * D_tmp;
    D[r3 + 9606] = maxval;
    D[r3 + 11207] = brm;
    D[r3 + 12808] = 2.0 * D_tmp;
    for (r1 = 0; r1 < 9; r1++) {
      b_y_tmp[r1 + 9 * r3] = D[r3 + 1601 * r1];
    }
  }

  for (r3 = 0; r3 < 9; r3++) {
    maxval = 0.0;
    for (r1 = 0; r1 < 1601; r1++) {
      maxval += b_y_tmp[r3 + 9 * r1];
    }

    v[r3] = maxval;
    for (r1 = 0; r1 < 9; r1++) {
      maxval = 0.0;
      for (r2 = 0; r2 < 1601; r2++) {
        maxval += b_y_tmp[r3 + 9 * r2] * D[r2 + 1601 * r1];
      }

      y_tmp[r3 + 9 * r1] = maxval;
    }
  }

  mldivide(y_tmp, v);

  //  least square fitting
  //  rotated ellipsoid
  A[0] = v[0];
  A[4] = v[3];
  A[8] = v[4];
  A[12] = v[6];
  A[1] = v[3];
  A[5] = v[1];
  A[9] = v[5];
  A[13] = v[7];
  A[2] = v[4];
  A[6] = v[5];
  A[10] = v[2];
  A[14] = v[8];
  A[3] = v[6];
  A[7] = v[7];
  A[11] = v[8];
  A[15] = -1.0;
  for (r3 = 0; r3 < 3; r3++) {
    r1 = r3 << 2;
    b_A[3 * r3] = -A[r1];
    b_A[3 * r3 + 1] = -A[r1 + 1];
    b_A[3 * r3 + 2] = -A[r1 + 2];
  }

  B[0] = v[6];
  B[1] = v[7];
  B[2] = v[8];
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = std::abs(b_A[0]);
  a21 = std::abs(b_A[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (std::abs(b_A[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] /= b_A[r1];
  b_A[r3] /= b_A[r1];
  b_A[r2 + 3] -= b_A[r2] * b_A[r1 + 3];
  b_A[r3 + 3] -= b_A[r3] * b_A[r1 + 3];
  b_A[r2 + 6] -= b_A[r2] * b_A[r1 + 6];
  b_A[r3 + 6] -= b_A[r3] * b_A[r1 + 6];
  if (std::abs(b_A[r3 + 3]) > std::abs(b_A[r2 + 3])) {
    int rtemp;
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b_A[r3 + 3] /= b_A[r2 + 3];
  b_A[r3 + 6] -= b_A[r3 + 3] * b_A[r2 + 6];
  ofs[1] = B[r2] - B[r1] * b_A[r2];
  ofs[2] = (B[r3] - B[r1] * b_A[r3]) - ofs[1] * b_A[r3 + 3];
  ofs[2] /= b_A[r3 + 6];
  ofs[0] = B[r1] - ofs[2] * b_A[r1 + 6];
  ofs[1] -= ofs[2] * b_A[r2 + 6];
  ofs[1] /= b_A[r2 + 3];
  ofs[0] -= ofs[1] * b_A[r1 + 3];
  ofs[0] /= b_A[r1];

  //  offset is center of ellipsoid
  for (r3 = 0; r3 < 16; r3++) {
    Tmtx[r3] = iv[r3];
  }

  Tmtx[3] = ofs[0];
  Tmtx[7] = ofs[1];
  Tmtx[11] = ofs[2];
  for (r3 = 0; r3 < 4; r3++) {
    maxval = Tmtx[r3 + 4];
    a21 = Tmtx[r3 + 8];
    brm = Tmtx[r3 + 12];
    for (r1 = 0; r1 < 4; r1++) {
      r2 = r1 << 2;
      b_Tmtx[r3 + r2] = ((Tmtx[r3] * A[r2] + maxval * A[r2 + 1]) + a21 * A[r2 +
                         2]) + brm * A[r2 + 3];
    }
  }

  for (r3 = 0; r3 < 4; r3++) {
    maxval = b_Tmtx[r3 + 4];
    a21 = b_Tmtx[r3 + 8];
    brm = b_Tmtx[r3 + 12];
    for (r1 = 0; r1 < 4; r1++) {
      A[r3 + (r1 << 2)] = ((b_Tmtx[r3] * Tmtx[r1] + maxval * Tmtx[r1 + 4]) + a21
                           * Tmtx[r1 + 8]) + brm * Tmtx[r1 + 12];
    }
  }

  //  ellipsoid translated to (0,0,0)
  for (r3 = 0; r3 < 3; r3++) {
    r1 = r3 << 2;
    b_A[3 * r3] = A[r1] / -A[15];
    b_A[3 * r3 + 1] = A[r1 + 1] / -A[15];
    b_A[3 * r3 + 2] = A[r1 + 2] / -A[15];
  }

  eig(b_A, rotM, ev);

  //  eigenvectors (rotation) and eigenvalues (gain)
  if (ev[0].im == 0.0) {
    gain[0].re = 1.0 / ev[0].re;
    gain[0].im = 0.0;
  } else if (ev[0].re == 0.0) {
    gain[0].re = 0.0;
    gain[0].im = -(1.0 / ev[0].im);
  } else {
    brm = std::abs(ev[0].re);
    maxval = std::abs(ev[0].im);
    if (brm > maxval) {
      maxval = ev[0].im / ev[0].re;
      a21 = ev[0].re + maxval * ev[0].im;
      gain[0].re = (1.0 + maxval * 0.0) / a21;
      gain[0].im = (0.0 - maxval) / a21;
    } else if (maxval == brm) {
      if (ev[0].re > 0.0) {
        maxval = 0.5;
      } else {
        maxval = -0.5;
      }

      if (ev[0].im > 0.0) {
        a21 = 0.5;
      } else {
        a21 = -0.5;
      }

      gain[0].re = (maxval + 0.0 * a21) / brm;
      gain[0].im = (0.0 * maxval - a21) / brm;
    } else {
      maxval = ev[0].re / ev[0].im;
      a21 = ev[0].im + maxval * ev[0].re;
      gain[0].re = maxval / a21;
      gain[0].im = (maxval * 0.0 - 1.0) / a21;
    }
  }

  if (ev[4].im == 0.0) {
    gain[1].re = 1.0 / ev[4].re;
    gain[1].im = 0.0;
  } else if (ev[4].re == 0.0) {
    gain[1].re = 0.0;
    gain[1].im = -(1.0 / ev[4].im);
  } else {
    brm = std::abs(ev[4].re);
    maxval = std::abs(ev[4].im);
    if (brm > maxval) {
      maxval = ev[4].im / ev[4].re;
      a21 = ev[4].re + maxval * ev[4].im;
      gain[1].re = (1.0 + maxval * 0.0) / a21;
      gain[1].im = (0.0 - maxval) / a21;
    } else if (maxval == brm) {
      if (ev[4].re > 0.0) {
        maxval = 0.5;
      } else {
        maxval = -0.5;
      }

      if (ev[4].im > 0.0) {
        a21 = 0.5;
      } else {
        a21 = -0.5;
      }

      gain[1].re = (maxval + 0.0 * a21) / brm;
      gain[1].im = (0.0 * maxval - a21) / brm;
    } else {
      maxval = ev[4].re / ev[4].im;
      a21 = ev[4].im + maxval * ev[4].re;
      gain[1].re = maxval / a21;
      gain[1].im = (maxval * 0.0 - 1.0) / a21;
    }
  }

  if (ev[8].im == 0.0) {
    gain[2].re = 1.0 / ev[8].re;
    gain[2].im = 0.0;
  } else if (ev[8].re == 0.0) {
    gain[2].re = 0.0;
    gain[2].im = -(1.0 / ev[8].im);
  } else {
    brm = std::abs(ev[8].re);
    maxval = std::abs(ev[8].im);
    if (brm > maxval) {
      maxval = ev[8].im / ev[8].re;
      a21 = ev[8].re + maxval * ev[8].im;
      gain[2].re = (1.0 + maxval * 0.0) / a21;
      gain[2].im = (0.0 - maxval) / a21;
    } else if (maxval == brm) {
      if (ev[8].re > 0.0) {
        maxval = 0.5;
      } else {
        maxval = -0.5;
      }

      if (ev[8].im > 0.0) {
        a21 = 0.5;
      } else {
        a21 = -0.5;
      }

      gain[2].re = (maxval + 0.0 * a21) / brm;
      gain[2].im = (0.0 * maxval - a21) / brm;
    } else {
      maxval = ev[8].re / ev[8].im;
      a21 = ev[8].im + maxval * ev[8].re;
      gain[2].re = maxval / a21;
      gain[2].im = (maxval * 0.0 - 1.0) / a21;
    }
  }

  b_sqrt(&gain[0]);
  b_sqrt(&gain[1]);
  b_sqrt(&gain[2]);

  //  gain is radius of the ellipsoid
}

//
// File trailer for ellipsoid_fit.cpp
//
// [EOF]
//
