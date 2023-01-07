//
// File: xzhgeqz.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 17-Jun-2020 10:37:31
//

// Include Files
#include "xzhgeqz.h"
#include "ellipsoid_fit.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xzlartg.h"
#include <cmath>

// Function Definitions

//
// Arguments    : creal_T A[9]
//                int ilo
//                int ihi
//                creal_T Z[9]
//                int *info
//                creal_T alpha1[3]
//                creal_T beta1[3]
// Return Type  : void
//
void xzhgeqz(creal_T A[9], int ilo, int ihi, creal_T Z[9], int *info, creal_T
             alpha1[3], creal_T beta1[3])
{
  double eshift_re;
  double eshift_im;
  creal_T ctemp;
  double anorm;
  double scale;
  double reAij;
  double sumsq;
  double b_atol;
  boolean_T firstNonZero;
  int j;
  int ctemp_tmp;
  double ascale;
  int i;
  int jp1;
  double imAij;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  double temp2;
  int ilast;
  creal_T shift;
  creal_T b_ascale;
  *info = 0;
  alpha1[0].re = 0.0;
  alpha1[0].im = 0.0;
  beta1[0].re = 1.0;
  beta1[0].im = 0.0;
  alpha1[1].re = 0.0;
  alpha1[1].im = 0.0;
  beta1[1].re = 1.0;
  beta1[1].im = 0.0;
  alpha1[2].re = 0.0;
  alpha1[2].im = 0.0;
  beta1[2].re = 1.0;
  beta1[2].im = 0.0;
  eshift_re = 0.0;
  eshift_im = 0.0;
  ctemp.re = 0.0;
  ctemp.im = 0.0;
  anorm = 0.0;
  if (ilo <= ihi) {
    scale = 0.0;
    sumsq = 0.0;
    firstNonZero = true;
    for (j = ilo; j <= ihi; j++) {
      ctemp_tmp = j + 1;
      if (ihi < j + 1) {
        ctemp_tmp = ihi;
      }

      for (i = ilo; i <= ctemp_tmp; i++) {
        jp1 = (i + 3 * (j - 1)) - 1;
        reAij = A[jp1].re;
        imAij = A[jp1].im;
        if (reAij != 0.0) {
          anorm = std::abs(reAij);
          if (firstNonZero) {
            sumsq = 1.0;
            scale = anorm;
            firstNonZero = false;
          } else if (scale < anorm) {
            temp2 = scale / anorm;
            sumsq = sumsq * temp2 * temp2 + 1.0;
            scale = anorm;
          } else {
            temp2 = anorm / scale;
            sumsq += temp2 * temp2;
          }
        }

        if (imAij != 0.0) {
          anorm = std::abs(imAij);
          if (firstNonZero) {
            sumsq = 1.0;
            scale = anorm;
            firstNonZero = false;
          } else if (scale < anorm) {
            temp2 = scale / anorm;
            sumsq = sumsq * temp2 * temp2 + 1.0;
            scale = anorm;
          } else {
            temp2 = anorm / scale;
            sumsq += temp2 * temp2;
          }
        }
      }
    }

    anorm = scale * std::sqrt(sumsq);
  }

  reAij = 2.2204460492503131E-16 * anorm;
  b_atol = 2.2250738585072014E-308;
  if (reAij > 2.2250738585072014E-308) {
    b_atol = reAij;
  }

  reAij = 2.2250738585072014E-308;
  if (anorm > 2.2250738585072014E-308) {
    reAij = anorm;
  }

  ascale = 1.0 / reAij;
  firstNonZero = true;
  ctemp_tmp = ihi + 1;
  for (j = ctemp_tmp; j < 4; j++) {
    alpha1[j - 1] = A[(j + 3 * (j - 1)) - 1];
  }

  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    int ifirst;
    int istart;
    int ilastm1;
    int iiter;
    boolean_T goto60;
    boolean_T goto70;
    boolean_T goto90;
    int jiter;
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (jiter <= 30 * ((ihi - ilo) + 1) - 1) {
        boolean_T b_guard1 = false;
        boolean_T exitg2;
        b_guard1 = false;
        if (ilast + 1 == ilo) {
          goto60 = true;
          b_guard1 = true;
        } else {
          ctemp_tmp = ilast + 3 * ilastm1;
          if (std::abs(A[ctemp_tmp].re) + std::abs(A[ctemp_tmp].im) <= b_atol) {
            A[ctemp_tmp].re = 0.0;
            A[ctemp_tmp].im = 0.0;
            goto60 = true;
            b_guard1 = true;
          } else {
            boolean_T guard3 = false;
            j = ilastm1;
            guard3 = false;
            exitg2 = false;
            while ((!exitg2) && (j + 1 >= ilo)) {
              if (j + 1 == ilo) {
                guard3 = true;
                exitg2 = true;
              } else {
                ctemp_tmp = j + 3 * (j - 1);
                if (std::abs(A[ctemp_tmp].re) + std::abs(A[ctemp_tmp].im) <=
                    b_atol) {
                  A[ctemp_tmp].re = 0.0;
                  A[ctemp_tmp].im = 0.0;
                  guard3 = true;
                  exitg2 = true;
                } else {
                  j--;
                  guard3 = false;
                }
              }
            }

            if (guard3) {
              ifirst = j + 1;
              goto70 = true;
            }

            if (goto70) {
              b_guard1 = true;
            } else {
              alpha1[0].re = rtNaN;
              alpha1[0].im = 0.0;
              beta1[0].re = rtNaN;
              beta1[0].im = 0.0;
              alpha1[1].re = rtNaN;
              alpha1[1].im = 0.0;
              beta1[1].re = rtNaN;
              beta1[1].im = 0.0;
              alpha1[2].re = rtNaN;
              alpha1[2].im = 0.0;
              beta1[2].re = rtNaN;
              beta1[2].im = 0.0;
              for (ctemp_tmp = 0; ctemp_tmp < 9; ctemp_tmp++) {
                Z[ctemp_tmp].re = rtNaN;
                Z[ctemp_tmp].im = 0.0;
              }

              *info = 1;
              exitg1 = 1;
            }
          }
        }

        if (b_guard1) {
          if (goto60) {
            goto60 = false;
            alpha1[ilast] = A[ilast + 3 * ilast];
            ilast = ilastm1;
            ilastm1--;
            if (ilast + 1 < ilo) {
              firstNonZero = false;
              guard2 = true;
              exitg1 = 1;
            } else {
              iiter = 0;
              eshift_re = 0.0;
              eshift_im = 0.0;
              jiter++;
            }
          } else {
            if (goto70) {
              double ad22_re;
              double ad22_im;
              goto70 = false;
              iiter++;
              if (iiter - iiter / 10 * 10 != 0) {
                double t1_re;
                double t1_im;
                double t1_im_tmp;
                jp1 = ilastm1 + 3 * ilastm1;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0) {
                  shift.re = anorm / 0.57735026918962584;
                  shift.im = 0.0;
                } else if (anorm == 0.0) {
                  shift.re = 0.0;
                  shift.im = reAij / 0.57735026918962584;
                } else {
                  shift.re = anorm / 0.57735026918962584;
                  shift.im = reAij / 0.57735026918962584;
                }

                jp1 = ilast + 3 * ilast;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0) {
                  ad22_re = anorm / 0.57735026918962584;
                  ad22_im = 0.0;
                } else if (anorm == 0.0) {
                  ad22_re = 0.0;
                  ad22_im = reAij / 0.57735026918962584;
                } else {
                  ad22_re = anorm / 0.57735026918962584;
                  ad22_im = reAij / 0.57735026918962584;
                }

                t1_re = 0.5 * (shift.re + ad22_re);
                t1_im = 0.5 * (shift.im + ad22_im);
                t1_im_tmp = t1_re * t1_im;
                jp1 = ilastm1 + 3 * ilast;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0) {
                  imAij = anorm / 0.57735026918962584;
                  temp2 = 0.0;
                } else if (anorm == 0.0) {
                  imAij = 0.0;
                  temp2 = reAij / 0.57735026918962584;
                } else {
                  imAij = anorm / 0.57735026918962584;
                  temp2 = reAij / 0.57735026918962584;
                }

                jp1 = ilast + 3 * ilastm1;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0) {
                  sumsq = anorm / 0.57735026918962584;
                  anorm = 0.0;
                } else if (anorm == 0.0) {
                  sumsq = 0.0;
                  anorm = reAij / 0.57735026918962584;
                } else {
                  sumsq = anorm / 0.57735026918962584;
                  anorm = reAij / 0.57735026918962584;
                }

                reAij = shift.re * ad22_re - shift.im * ad22_im;
                scale = shift.re * ad22_im + shift.im * ad22_re;
                shift.re = ((t1_re * t1_re - t1_im * t1_im) + (imAij * sumsq -
                  temp2 * anorm)) - reAij;
                shift.im = ((t1_im_tmp + t1_im_tmp) + (imAij * anorm + temp2 *
                  sumsq)) - scale;
                b_sqrt(&shift);
                if ((t1_re - ad22_re) * shift.re + (t1_im - ad22_im) * shift.im <=
                    0.0) {
                  shift.re += t1_re;
                  shift.im += t1_im;
                } else {
                  shift.re = t1_re - shift.re;
                  shift.im = t1_im - shift.im;
                }
              } else {
                jp1 = ilast + 3 * ilastm1;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0) {
                  imAij = anorm / 0.57735026918962584;
                  temp2 = 0.0;
                } else if (anorm == 0.0) {
                  imAij = 0.0;
                  temp2 = reAij / 0.57735026918962584;
                } else {
                  imAij = anorm / 0.57735026918962584;
                  temp2 = reAij / 0.57735026918962584;
                }

                eshift_re += imAij;
                eshift_im += temp2;
                shift.re = eshift_re;
                shift.im = eshift_im;
              }

              j = ilastm1;
              jp1 = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (j + 1 > ifirst)) {
                istart = j + 1;
                ctemp_tmp = j + 3 * j;
                ctemp.re = ascale * A[ctemp_tmp].re - shift.re *
                  0.57735026918962584;
                ctemp.im = ascale * A[ctemp_tmp].im - shift.im *
                  0.57735026918962584;
                anorm = std::abs(ctemp.re) + std::abs(ctemp.im);
                jp1 += 3 * j;
                temp2 = ascale * (std::abs(A[jp1].re) + std::abs(A[jp1].im));
                reAij = anorm;
                if (temp2 > anorm) {
                  reAij = temp2;
                }

                if ((reAij < 1.0) && (reAij != 0.0)) {
                  anorm /= reAij;
                  temp2 /= reAij;
                }

                ctemp_tmp = j + 3 * (j - 1);
                if ((std::abs(A[ctemp_tmp].re) + std::abs(A[ctemp_tmp].im)) *
                    temp2 <= anorm * b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  jp1 = j;
                  j--;
                }
              }

              if (!goto90) {
                istart = ifirst;
                ctemp_tmp = (ifirst + 3 * (ifirst - 1)) - 1;
                ctemp.re = ascale * A[ctemp_tmp].re - shift.re *
                  0.57735026918962584;
                ctemp.im = ascale * A[ctemp_tmp].im - shift.im *
                  0.57735026918962584;
              }

              goto90 = false;
              jp1 = istart + 3 * (istart - 1);
              b_ascale.re = ascale * A[jp1].re;
              b_ascale.im = ascale * A[jp1].im;
              b_xzlartg(ctemp, b_ascale, &anorm, &shift);
              j = istart;
              jp1 = istart - 2;
              while (j < ilast + 1) {
                int ad22_re_tmp;
                if (j > istart) {
                  ctemp_tmp = j + 3 * jp1;
                  xzlartg(A[3 * jp1 + 1], A[ctemp_tmp], &anorm, &shift, &A[3 *
                          jp1 + 1]);
                  A[ctemp_tmp].re = 0.0;
                  A[ctemp_tmp].im = 0.0;
                }

                for (jp1 = j; jp1 < 4; jp1++) {
                  ctemp_tmp = j + 3 * (jp1 - 1);
                  ad22_re_tmp = ctemp_tmp - 1;
                  ad22_re = anorm * A[ad22_re_tmp].re + (shift.re * A[ctemp_tmp]
                    .re - shift.im * A[ctemp_tmp].im);
                  ad22_im = anorm * A[ad22_re_tmp].im + (shift.re * A[ctemp_tmp]
                    .im + shift.im * A[ctemp_tmp].re);
                  reAij = A[ad22_re_tmp].im;
                  scale = A[ad22_re_tmp].re;
                  A[ctemp_tmp].re = anorm * A[ctemp_tmp].re - (shift.re *
                    A[ad22_re_tmp].re + shift.im * A[ad22_re_tmp].im);
                  A[ctemp_tmp].im = anorm * A[ctemp_tmp].im - (shift.re * reAij
                    - shift.im * scale);
                  A[ad22_re_tmp].re = ad22_re;
                  A[ad22_re_tmp].im = ad22_im;
                }

                shift.re = -shift.re;
                shift.im = -shift.im;
                jp1 = j;
                if (ilast + 1 < j + 2) {
                  jp1 = ilast - 1;
                }

                for (i = 1; i <= jp1 + 2; i++) {
                  ctemp_tmp = (i + 3 * (j - 1)) - 1;
                  ad22_re_tmp = (i + 3 * j) - 1;
                  ad22_re = anorm * A[ad22_re_tmp].re + (shift.re * A[ctemp_tmp]
                    .re - shift.im * A[ctemp_tmp].im);
                  ad22_im = anorm * A[ad22_re_tmp].im + (shift.re * A[ctemp_tmp]
                    .im + shift.im * A[ctemp_tmp].re);
                  reAij = A[ad22_re_tmp].im;
                  scale = A[ad22_re_tmp].re;
                  A[ctemp_tmp].re = anorm * A[ctemp_tmp].re - (shift.re *
                    A[ad22_re_tmp].re + shift.im * A[ad22_re_tmp].im);
                  A[ctemp_tmp].im = anorm * A[ctemp_tmp].im - (shift.re * reAij
                    - shift.im * scale);
                  A[ad22_re_tmp].re = ad22_re;
                  A[ad22_re_tmp].im = ad22_im;
                }

                ctemp_tmp = 3 * (j - 1);
                ad22_re = anorm * Z[3 * j].re + (shift.re * Z[ctemp_tmp].re -
                  shift.im * Z[ctemp_tmp].im);
                ad22_im = anorm * Z[3 * j].im + (shift.re * Z[ctemp_tmp].im +
                  shift.im * Z[ctemp_tmp].re);
                reAij = Z[3 * j].im;
                scale = Z[3 * j].re;
                Z[ctemp_tmp].re = anorm * Z[ctemp_tmp].re - (shift.re * Z[3 * j]
                  .re + shift.im * Z[3 * j].im);
                Z[ctemp_tmp].im = anorm * Z[ctemp_tmp].im - (shift.re * reAij -
                  shift.im * scale);
                Z[3 * j].re = ad22_re;
                Z[3 * j].im = ad22_im;
                jp1 = ctemp_tmp + 1;
                ad22_re_tmp = 3 * j + 1;
                ad22_re = anorm * Z[ad22_re_tmp].re + (shift.re * Z[jp1].re -
                  shift.im * Z[jp1].im);
                ad22_im = anorm * Z[ad22_re_tmp].im + (shift.re * Z[jp1].im +
                  shift.im * Z[jp1].re);
                reAij = Z[ad22_re_tmp].im;
                scale = Z[ad22_re_tmp].re;
                Z[jp1].re = anorm * Z[jp1].re - (shift.re * Z[ad22_re_tmp].re +
                  shift.im * Z[ad22_re_tmp].im);
                Z[jp1].im = anorm * Z[jp1].im - (shift.re * reAij - shift.im *
                  scale);
                Z[ad22_re_tmp].re = ad22_re;
                Z[ad22_re_tmp].im = ad22_im;
                ctemp_tmp += 2;
                ad22_re_tmp = 3 * j + 2;
                ad22_re = anorm * Z[ad22_re_tmp].re + (shift.re * Z[ctemp_tmp].
                  re - shift.im * Z[ctemp_tmp].im);
                ad22_im = anorm * Z[ad22_re_tmp].im + (shift.re * Z[ctemp_tmp].
                  im + shift.im * Z[ctemp_tmp].re);
                reAij = Z[ad22_re_tmp].im;
                scale = Z[ad22_re_tmp].re;
                Z[ctemp_tmp].re = anorm * Z[ctemp_tmp].re - (shift.re *
                  Z[ad22_re_tmp].re + shift.im * Z[ad22_re_tmp].im);
                Z[ctemp_tmp].im = anorm * Z[ctemp_tmp].im - (shift.re * reAij -
                  shift.im * scale);
                Z[ad22_re_tmp].re = ad22_re;
                Z[ad22_re_tmp].im = ad22_im;
                jp1 = j - 1;
                j++;
              }
            }

            jiter++;
          }
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }

  if (guard2) {
    if (firstNonZero) {
      *info = ilast + 1;
      for (jp1 = 0; jp1 <= ilast; jp1++) {
        alpha1[jp1].re = rtNaN;
        alpha1[jp1].im = 0.0;
        beta1[jp1].re = rtNaN;
        beta1[jp1].im = 0.0;
      }

      for (ctemp_tmp = 0; ctemp_tmp < 9; ctemp_tmp++) {
        Z[ctemp_tmp].re = rtNaN;
        Z[ctemp_tmp].im = 0.0;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    for (j = 0; j <= ilo - 2; j++) {
      alpha1[j] = A[j + 3 * j];
    }
  }
}

//
// File trailer for xzhgeqz.cpp
//
// [EOF]
//
