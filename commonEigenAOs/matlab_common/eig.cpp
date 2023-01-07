//
// File: eig.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 17-Jun-2020 10:37:31
//

// Include Files
#include "eig.h"
#include "ellipsoid_fit.h"
#include "rt_nonfinite.h"
#include "xgehrd.h"
#include "xgerc.h"
#include "xhseqr.h"
#include "xzggev.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : const double A[9]
//                creal_T V[9]
//                creal_T D[9]
// Return Type  : void
//
void eig(const double A[9], creal_T V[9], creal_T D[9])
{
  boolean_T p;
  int info;
  creal_T At[9];
  creal_T alpha1[3];
  creal_T beta1[3];
  int coltop;
  double b_A[9];
  double colnorm;
  double tau[2];
  double scale;
  double b_V[9];
  double work[3];
  int iac;
  p = true;
  for (info = 0; info < 9; info++) {
    if ((!p) || (rtIsInf(A[info]) || rtIsNaN(A[info]))) {
      p = false;
    }
  }

  if (!p) {
    for (int i = 0; i < 9; i++) {
      V[i].re = rtNaN;
      V[i].im = 0.0;
      D[i].re = 0.0;
      D[i].im = 0.0;
    }

    D[0].re = rtNaN;
    D[0].im = 0.0;
    D[4].re = rtNaN;
    D[4].im = 0.0;
    D[8].re = rtNaN;
    D[8].im = 0.0;
  } else {
    int kend;
    boolean_T exitg2;
    int exitg1;
    p = true;
    kend = 0;
    exitg2 = false;
    while ((!exitg2) && (kend < 3)) {
      info = 0;
      do {
        exitg1 = 0;
        if (info <= kend) {
          if (!(A[info + 3 * kend] == A[kend + 3 * info])) {
            p = false;
            exitg1 = 1;
          } else {
            info++;
          }
        } else {
          kend++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }

    if (p) {
      int i;
      p = true;
      for (info = 0; info < 9; info++) {
        if ((!p) || (rtIsInf(A[info]) || rtIsNaN(A[info]))) {
          p = false;
        }
      }

      if (!p) {
        for (i = 0; i < 9; i++) {
          b_V[i] = rtNaN;
        }

        for (info = 2; info < 4; info++) {
          b_V[info - 1] = 0.0;
        }

        b_V[5] = 0.0;
        for (i = 0; i < 9; i++) {
          b_A[i] = rtNaN;
        }
      } else {
        int lastv;
        std::memcpy(&b_A[0], &A[0], 9U * sizeof(double));
        xgehrd(b_A, tau);
        std::memcpy(&b_V[0], &b_A[0], 9U * sizeof(double));
        for (info = 0; info < 2; info++) {
          b_V[info + 6] = 0.0;
        }

        b_V[3] = 0.0;
        scale = b_V[2];
        b_V[5] = scale;
        b_V[1] = 0.0;
        b_V[2] = 0.0;
        b_V[0] = 1.0;
        work[0] = 0.0;
        work[1] = 0.0;
        work[2] = 0.0;
        b_V[8] = 1.0 - tau[1];
        b_V[7] = 0.0;
        b_V[4] = 1.0;
        if (tau[0] != 0.0) {
          lastv = 2;
          info = 8;
          while ((lastv > 0) && (b_V[info - 3] == 0.0)) {
            lastv--;
            info--;
          }

          info = 1;
          kend = 8;
          do {
            exitg1 = 0;
            if (kend <= lastv + 7) {
              if (b_V[kend - 1] != 0.0) {
                exitg1 = 1;
              } else {
                kend++;
              }
            } else {
              info = 0;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        } else {
          lastv = 0;
          info = 0;
        }

        if (lastv > 0) {
          if (info != 0) {
            work[0] = 0.0;
            coltop = 0;
            i = lastv + 7;
            for (iac = 8; iac <= 8; iac += 3) {
              int ix;
              ix = 8;
              scale = 0.0;
              for (kend = 8; kend <= i; kend++) {
                scale += b_V[kend - 1] * b_V[ix - 4];
                ix++;
              }

              work[coltop] += scale;
              coltop++;
            }
          }

          xgerc(lastv, info, -tau[0], 5, work, b_V, 8);
        }

        for (info = 6; info < 7; info++) {
          b_V[5] *= -tau[0];
        }

        b_V[4] = 1.0 - tau[0];
        xhseqr(b_A, b_V);
      }

      for (i = 0; i < 9; i++) {
        V[i].re = b_V[i];
        V[i].im = 0.0;
      }

      b_A[1] = 0.0;
      b_A[3] = 0.0;
      b_A[5] = 0.0;
      for (info = 0; info < 2; info++) {
        b_A[info + 6] = 0.0;
      }

      for (i = 0; i < 9; i++) {
        D[i].re = b_A[i];
        D[i].im = 0.0;
      }
    } else {
      int i;
      double t;
      double absxk;
      for (i = 0; i < 9; i++) {
        At[i].re = A[i];
        At[i].im = 0.0;
      }

      xzggev(At, &info, alpha1, beta1, V);
      for (coltop = 0; coltop <= 6; coltop += 3) {
        colnorm = 0.0;
        scale = 3.3121686421112381E-170;
        kend = coltop + 3;
        for (info = coltop + 1; info <= kend; info++) {
          absxk = std::abs(V[info - 1].re);
          if (absxk > scale) {
            t = scale / absxk;
            colnorm = colnorm * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            colnorm += t * t;
          }

          absxk = std::abs(V[info - 1].im);
          if (absxk > scale) {
            t = scale / absxk;
            colnorm = colnorm * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            colnorm += t * t;
          }
        }

        colnorm = scale * std::sqrt(colnorm);
        i = coltop + 3;
        for (kend = coltop + 1; kend <= i; kend++) {
          scale = V[kend - 1].re;
          t = V[kend - 1].im;
          if (t == 0.0) {
            absxk = scale / colnorm;
            scale = 0.0;
          } else if (scale == 0.0) {
            absxk = 0.0;
            scale = t / colnorm;
          } else {
            absxk = scale / colnorm;
            scale = t / colnorm;
          }

          V[kend - 1].re = absxk;
          V[kend - 1].im = scale;
        }
      }

      std::memset(&D[0], 0, 9U * sizeof(creal_T));
      if (beta1[0].im == 0.0) {
        if (alpha1[0].im == 0.0) {
          D[0].re = alpha1[0].re / beta1[0].re;
          D[0].im = 0.0;
        } else if (alpha1[0].re == 0.0) {
          D[0].re = 0.0;
          D[0].im = alpha1[0].im / beta1[0].re;
        } else {
          D[0].re = alpha1[0].re / beta1[0].re;
          D[0].im = alpha1[0].im / beta1[0].re;
        }
      } else if (beta1[0].re == 0.0) {
        if (alpha1[0].re == 0.0) {
          D[0].re = alpha1[0].im / beta1[0].im;
          D[0].im = 0.0;
        } else if (alpha1[0].im == 0.0) {
          D[0].re = 0.0;
          D[0].im = -(alpha1[0].re / beta1[0].im);
        } else {
          D[0].re = alpha1[0].im / beta1[0].im;
          D[0].im = -(alpha1[0].re / beta1[0].im);
        }
      } else {
        t = std::abs(beta1[0].re);
        scale = std::abs(beta1[0].im);
        if (t > scale) {
          scale = beta1[0].im / beta1[0].re;
          absxk = beta1[0].re + scale * beta1[0].im;
          D[0].re = (alpha1[0].re + scale * alpha1[0].im) / absxk;
          D[0].im = (alpha1[0].im - scale * alpha1[0].re) / absxk;
        } else if (scale == t) {
          if (beta1[0].re > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }

          if (beta1[0].im > 0.0) {
            absxk = 0.5;
          } else {
            absxk = -0.5;
          }

          D[0].re = (alpha1[0].re * scale + alpha1[0].im * absxk) / t;
          D[0].im = (alpha1[0].im * scale - alpha1[0].re * absxk) / t;
        } else {
          scale = beta1[0].re / beta1[0].im;
          absxk = beta1[0].im + scale * beta1[0].re;
          D[0].re = (scale * alpha1[0].re + alpha1[0].im) / absxk;
          D[0].im = (scale * alpha1[0].im - alpha1[0].re) / absxk;
        }
      }

      if (beta1[1].im == 0.0) {
        if (alpha1[1].im == 0.0) {
          D[4].re = alpha1[1].re / beta1[1].re;
          D[4].im = 0.0;
        } else if (alpha1[1].re == 0.0) {
          D[4].re = 0.0;
          D[4].im = alpha1[1].im / beta1[1].re;
        } else {
          D[4].re = alpha1[1].re / beta1[1].re;
          D[4].im = alpha1[1].im / beta1[1].re;
        }
      } else if (beta1[1].re == 0.0) {
        if (alpha1[1].re == 0.0) {
          D[4].re = alpha1[1].im / beta1[1].im;
          D[4].im = 0.0;
        } else if (alpha1[1].im == 0.0) {
          D[4].re = 0.0;
          D[4].im = -(alpha1[1].re / beta1[1].im);
        } else {
          D[4].re = alpha1[1].im / beta1[1].im;
          D[4].im = -(alpha1[1].re / beta1[1].im);
        }
      } else {
        t = std::abs(beta1[1].re);
        scale = std::abs(beta1[1].im);
        if (t > scale) {
          scale = beta1[1].im / beta1[1].re;
          absxk = beta1[1].re + scale * beta1[1].im;
          D[4].re = (alpha1[1].re + scale * alpha1[1].im) / absxk;
          D[4].im = (alpha1[1].im - scale * alpha1[1].re) / absxk;
        } else if (scale == t) {
          if (beta1[1].re > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }

          if (beta1[1].im > 0.0) {
            absxk = 0.5;
          } else {
            absxk = -0.5;
          }

          D[4].re = (alpha1[1].re * scale + alpha1[1].im * absxk) / t;
          D[4].im = (alpha1[1].im * scale - alpha1[1].re * absxk) / t;
        } else {
          scale = beta1[1].re / beta1[1].im;
          absxk = beta1[1].im + scale * beta1[1].re;
          D[4].re = (scale * alpha1[1].re + alpha1[1].im) / absxk;
          D[4].im = (scale * alpha1[1].im - alpha1[1].re) / absxk;
        }
      }

      if (beta1[2].im == 0.0) {
        if (alpha1[2].im == 0.0) {
          D[8].re = alpha1[2].re / beta1[2].re;
          D[8].im = 0.0;
        } else if (alpha1[2].re == 0.0) {
          D[8].re = 0.0;
          D[8].im = alpha1[2].im / beta1[2].re;
        } else {
          D[8].re = alpha1[2].re / beta1[2].re;
          D[8].im = alpha1[2].im / beta1[2].re;
        }
      } else if (beta1[2].re == 0.0) {
        if (alpha1[2].re == 0.0) {
          D[8].re = alpha1[2].im / beta1[2].im;
          D[8].im = 0.0;
        } else if (alpha1[2].im == 0.0) {
          D[8].re = 0.0;
          D[8].im = -(alpha1[2].re / beta1[2].im);
        } else {
          D[8].re = alpha1[2].im / beta1[2].im;
          D[8].im = -(alpha1[2].re / beta1[2].im);
        }
      } else {
        t = std::abs(beta1[2].re);
        scale = std::abs(beta1[2].im);
        if (t > scale) {
          scale = beta1[2].im / beta1[2].re;
          absxk = beta1[2].re + scale * beta1[2].im;
          D[8].re = (alpha1[2].re + scale * alpha1[2].im) / absxk;
          D[8].im = (alpha1[2].im - scale * alpha1[2].re) / absxk;
        } else if (scale == t) {
          if (beta1[2].re > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }

          if (beta1[2].im > 0.0) {
            absxk = 0.5;
          } else {
            absxk = -0.5;
          }

          D[8].re = (alpha1[2].re * scale + alpha1[2].im * absxk) / t;
          D[8].im = (alpha1[2].im * scale - alpha1[2].re * absxk) / t;
        } else {
          scale = beta1[2].re / beta1[2].im;
          absxk = beta1[2].im + scale * beta1[2].re;
          D[8].re = (scale * alpha1[2].re + alpha1[2].im) / absxk;
          D[8].im = (scale * alpha1[2].im - alpha1[2].re) / absxk;
        }
      }
    }
  }
}

//
// File trailer for eig.cpp
//
// [EOF]
//
