//
// File: mldivide.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 17-Jun-2020 10:37:31
//

// Include Files
#include "mldivide.h"
#include "ellipsoid_fit.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : const double A[81]
//                double B[9]
// Return Type  : void
//
void mldivide(const double A[81], double B[9])
{
  double b_A[81];
  int i;
  signed char ipiv[9];
  int k;
  int iy;
  int jA;
  int ix;
  std::memcpy(&b_A[0], &A[0], 81U * sizeof(double));
  for (i = 0; i < 9; i++) {
    ipiv[i] = static_cast<signed char>(i + 1);
  }

  for (int j = 0; j < 8; j++) {
    int mmj_tmp;
    int b;
    int jj;
    int jp1j;
    double smax;
    mmj_tmp = 7 - j;
    b = j * 10;
    jj = j * 10;
    jp1j = b + 2;
    iy = 9 - j;
    jA = 0;
    ix = b;
    smax = std::abs(b_A[jj]);
    for (k = 2; k <= iy; k++) {
      double s;
      ix++;
      s = std::abs(b_A[ix]);
      if (s > smax) {
        jA = k - 1;
        smax = s;
      }
    }

    if (b_A[jj + jA] != 0.0) {
      if (jA != 0) {
        iy = j + jA;
        ipiv[j] = static_cast<signed char>(iy + 1);
        ix = j;
        for (k = 0; k < 9; k++) {
          smax = b_A[ix];
          b_A[ix] = b_A[iy];
          b_A[iy] = smax;
          ix += 9;
          iy += 9;
        }
      }

      i = (jj - j) + 9;
      for (jA = jp1j; jA <= i; jA++) {
        b_A[jA - 1] /= b_A[jj];
      }
    }

    iy = b + 9;
    jA = jj;
    for (jp1j = 0; jp1j <= mmj_tmp; jp1j++) {
      smax = b_A[iy];
      if (b_A[iy] != 0.0) {
        ix = jj + 1;
        i = jA + 11;
        b = (jA - j) + 18;
        for (k = i; k <= b; k++) {
          b_A[k - 1] += b_A[ix] * -smax;
          ix++;
        }
      }

      iy += 9;
      jA += 9;
    }

    if (ipiv[j] != j + 1) {
      smax = B[j];
      i = ipiv[j] - 1;
      B[j] = B[i];
      B[i] = smax;
    }
  }

  for (k = 0; k < 9; k++) {
    iy = 9 * k;
    if (B[k] != 0.0) {
      i = k + 2;
      for (jA = i; jA < 10; jA++) {
        B[jA - 1] -= B[k] * b_A[(jA + iy) - 1];
      }
    }
  }

  for (k = 8; k >= 0; k--) {
    iy = 9 * k;
    if (B[k] != 0.0) {
      B[k] /= b_A[k + iy];
      for (jA = 0; jA < k; jA++) {
        B[jA] -= B[k] * b_A[jA + iy];
      }
    }
  }
}

//
// File trailer for mldivide.cpp
//
// [EOF]
//
