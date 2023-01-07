//
// File: xztgevc.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 17-Jun-2020 10:37:31
//

// Include Files
#include "xztgevc.h"
#include "ellipsoid_fit.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const creal_T A[9]
//                creal_T V[9]
// Return Type  : void
//
void xztgevc(const creal_T A[9], creal_T V[9])
{
  double rworka_idx_1;
  double rworka_idx_2;
  double anorm;
  int i;
  double d_re;
  double ascale;
  double salpha_re;
  double salpha_im;
  double acoeff;
  creal_T work1[3];
  creal_T work2[3];
  rworka_idx_1 = 0.0;
  rworka_idx_2 = 0.0;
  anorm = std::abs(A[0].re) + std::abs(A[0].im);
  for (i = 0; i < 1; i++) {
    rworka_idx_1 += std::abs(A[3].re) + std::abs(A[3].im);
  }

  d_re = rworka_idx_1 + (std::abs(A[4].re) + std::abs(A[4].im));
  if (d_re > anorm) {
    anorm = d_re;
  }

  for (i = 0; i < 2; i++) {
    rworka_idx_2 += std::abs(A[i + 6].re) + std::abs(A[i + 6].im);
  }

  d_re = rworka_idx_2 + (std::abs(A[8].re) + std::abs(A[8].im));
  if (d_re > anorm) {
    anorm = d_re;
  }

  rworka_idx_2 = anorm;
  if (2.2250738585072014E-308 > anorm) {
    rworka_idx_2 = 2.2250738585072014E-308;
  }

  ascale = 1.0 / rworka_idx_2;
  for (int je = 0; je < 3; je++) {
    int x_tmp_tmp_tmp;
    double temp;
    boolean_T lscalea;
    double z;
    boolean_T lscaleb;
    double scale;
    double dmin;
    int b_i;
    int jr;
    x_tmp_tmp_tmp = 3 * (2 - je);
    i = (x_tmp_tmp_tmp - je) + 2;
    rworka_idx_2 = (std::abs(A[i].re) + std::abs(A[i].im)) * ascale;
    if (1.0 > rworka_idx_2) {
      rworka_idx_2 = 1.0;
    }

    temp = 1.0 / rworka_idx_2;
    salpha_re = ascale * (temp * A[i].re);
    salpha_im = ascale * (temp * A[i].im);
    acoeff = temp * ascale;
    if ((temp >= 2.2250738585072014E-308) && (acoeff < 3.0062525400134592E-292))
    {
      lscalea = true;
    } else {
      lscalea = false;
    }

    z = std::abs(salpha_re) + std::abs(salpha_im);
    if ((z >= 2.2250738585072014E-308) && (z < 3.0062525400134592E-292)) {
      lscaleb = true;
    } else {
      lscaleb = false;
    }

    scale = 1.0;
    if (lscalea) {
      rworka_idx_2 = anorm;
      if (3.3264005158911995E+291 < anorm) {
        rworka_idx_2 = 3.3264005158911995E+291;
      }

      scale = 3.0062525400134592E-292 / temp * rworka_idx_2;
    }

    if (lscaleb) {
      d_re = 3.0062525400134592E-292 / z;
      if (d_re > scale) {
        scale = d_re;
      }
    }

    if (lscalea || lscaleb) {
      rworka_idx_2 = acoeff;
      if (1.0 > acoeff) {
        rworka_idx_2 = 1.0;
      }

      if (z > rworka_idx_2) {
        rworka_idx_2 = z;
      }

      d_re = 1.0 / (2.2250738585072014E-308 * rworka_idx_2);
      if (d_re < scale) {
        scale = d_re;
      }

      if (lscalea) {
        acoeff = ascale * (scale * temp);
      } else {
        acoeff *= scale;
      }

      salpha_re *= scale;
      salpha_im *= scale;
    }

    work1[0].re = 0.0;
    work1[0].im = 0.0;
    work1[1].re = 0.0;
    work1[1].im = 0.0;
    work1[2].re = 0.0;
    work1[2].im = 0.0;
    work1[2 - je].re = 1.0;
    work1[2 - je].im = 0.0;
    dmin = 2.2204460492503131E-16 * acoeff * anorm;
    d_re = 2.2204460492503131E-16 * (std::abs(salpha_re) + std::abs(salpha_im));
    if (d_re > dmin) {
      dmin = d_re;
    }

    if (2.2250738585072014E-308 > dmin) {
      dmin = 2.2250738585072014E-308;
    }

    b_i = 1 - je;
    for (jr = 0; jr <= b_i; jr++) {
      i = jr + x_tmp_tmp_tmp;
      work1[jr].re = acoeff * A[i].re;
      work1[jr].im = acoeff * A[i].im;
    }

    work1[2 - je].re = 1.0;
    work1[2 - je].im = 0.0;
    b_i = static_cast<int>(((-1.0 - ((-static_cast<double>(je) + 3.0) - 1.0)) +
      1.0) / -1.0);
    for (int j = 0; j < b_i; j++) {
      int b_j;
      double d_im;
      double brm;
      b_j = 1 - (je + j);
      i = b_j + 3 * b_j;
      d_re = acoeff * A[i].re - salpha_re;
      d_im = acoeff * A[i].im - salpha_im;
      if (std::abs(d_re) + std::abs(d_im) <= dmin) {
        d_re = dmin;
        d_im = 0.0;
      }

      brm = std::abs(d_re);
      scale = std::abs(d_im);
      rworka_idx_2 = brm + scale;
      if (rworka_idx_2 < 1.0) {
        z = std::abs(work1[b_j].re) + std::abs(work1[b_j].im);
        if (z >= 1.4980776123852632E+307 * rworka_idx_2) {
          temp = 1.0 / z;
          i = 2 - je;
          for (jr = 0; jr <= i; jr++) {
            work1[jr].re *= temp;
            work1[jr].im *= temp;
          }
        }
      }

      if (d_im == 0.0) {
        if (-work1[b_j].im == 0.0) {
          scale = -work1[b_j].re / d_re;
          rworka_idx_2 = 0.0;
        } else if (-work1[b_j].re == 0.0) {
          scale = 0.0;
          rworka_idx_2 = -work1[b_j].im / d_re;
        } else {
          scale = -work1[b_j].re / d_re;
          rworka_idx_2 = -work1[b_j].im / d_re;
        }
      } else if (d_re == 0.0) {
        if (-work1[b_j].re == 0.0) {
          scale = -work1[b_j].im / d_im;
          rworka_idx_2 = 0.0;
        } else if (-work1[b_j].im == 0.0) {
          scale = 0.0;
          rworka_idx_2 = -(-work1[b_j].re / d_im);
        } else {
          scale = -work1[b_j].im / d_im;
          rworka_idx_2 = -(-work1[b_j].re / d_im);
        }
      } else if (brm > scale) {
        z = d_im / d_re;
        rworka_idx_2 = d_re + z * d_im;
        scale = (-work1[b_j].re + z * -work1[b_j].im) / rworka_idx_2;
        rworka_idx_2 = (-work1[b_j].im - z * -work1[b_j].re) / rworka_idx_2;
      } else if (scale == brm) {
        if (d_re > 0.0) {
          z = 0.5;
        } else {
          z = -0.5;
        }

        if (d_im > 0.0) {
          rworka_idx_2 = 0.5;
        } else {
          rworka_idx_2 = -0.5;
        }

        scale = (-work1[b_j].re * z + -work1[b_j].im * rworka_idx_2) / brm;
        rworka_idx_2 = (-work1[b_j].im * z - -work1[b_j].re * rworka_idx_2) /
          brm;
      } else {
        z = d_re / d_im;
        rworka_idx_2 = d_im + z * d_re;
        scale = (z * -work1[b_j].re + -work1[b_j].im) / rworka_idx_2;
        rworka_idx_2 = (z * -work1[b_j].im - (-work1[b_j].re)) / rworka_idx_2;
      }

      work1[b_j].re = scale;
      work1[b_j].im = rworka_idx_2;
      if (b_j + 1 > 1) {
        rworka_idx_2 = std::abs(work1[1].re) + std::abs(work1[1].im);
        if (rworka_idx_2 > 1.0) {
          temp = 1.0 / rworka_idx_2;
          if (acoeff * rworka_idx_1 >= 1.4980776123852632E+307 * temp) {
            i = 2 - je;
            for (jr = 0; jr <= i; jr++) {
              work1[jr].re *= temp;
              work1[jr].im *= temp;
            }
          }
        }

        d_re = acoeff * work1[1].re;
        d_im = acoeff * work1[1].im;
        work1[0].re += d_re * A[3].re - d_im * A[3].im;
        work1[0].im += d_re * A[3].im + d_im * A[3].re;
      }
    }

    work2[0].re = 0.0;
    work2[0].im = 0.0;
    work2[1].re = 0.0;
    work2[1].im = 0.0;
    work2[2].re = 0.0;
    work2[2].im = 0.0;
    b_i = 2 - je;
    for (jr = 0; jr <= b_i; jr++) {
      work2[0].re += V[3 * jr].re * work1[jr].re - V[3 * jr].im * work1[jr].im;
      work2[0].im += V[3 * jr].re * work1[jr].im + V[3 * jr].im * work1[jr].re;
      i = 3 * jr + 1;
      work2[1].re += V[i].re * work1[jr].re - V[i].im * work1[jr].im;
      work2[1].im += V[i].re * work1[jr].im + V[i].im * work1[jr].re;
      i = 3 * jr + 2;
      work2[2].re += V[i].re * work1[jr].re - V[i].im * work1[jr].im;
      work2[2].im += V[i].re * work1[jr].im + V[i].im * work1[jr].re;
    }

    rworka_idx_2 = std::abs(work2[0].re) + std::abs(work2[0].im);
    d_re = std::abs(work2[1].re) + std::abs(work2[1].im);
    if (d_re > rworka_idx_2) {
      rworka_idx_2 = d_re;
    }

    d_re = std::abs(work2[2].re) + std::abs(work2[2].im);
    if (d_re > rworka_idx_2) {
      rworka_idx_2 = d_re;
    }

    if (rworka_idx_2 > 2.2250738585072014E-308) {
      temp = 1.0 / rworka_idx_2;
      V[x_tmp_tmp_tmp].re = temp * work2[0].re;
      V[x_tmp_tmp_tmp].im = temp * work2[0].im;
      b_i = x_tmp_tmp_tmp + 1;
      V[b_i].re = temp * work2[1].re;
      V[b_i].im = temp * work2[1].im;
      b_i = x_tmp_tmp_tmp + 2;
      V[b_i].re = temp * work2[2].re;
      V[b_i].im = temp * work2[2].im;
    } else {
      V[x_tmp_tmp_tmp].re = 0.0;
      V[x_tmp_tmp_tmp].im = 0.0;
      b_i = x_tmp_tmp_tmp + 1;
      V[b_i].re = 0.0;
      V[b_i].im = 0.0;
      b_i = x_tmp_tmp_tmp + 2;
      V[b_i].re = 0.0;
      V[b_i].im = 0.0;
    }
  }
}

//
// File trailer for xztgevc.cpp
//
// [EOF]
//
