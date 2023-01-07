//
// File: xhseqr.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 17-Jun-2020 10:37:31
//

// Include Files
#include "xhseqr.h"
#include "ellipsoid_fit.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xzlarfg.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double h[9]
//                double z[9]
// Return Type  : int
//
int xhseqr(double h[9], double z[9])
{
  int info;
  double v[3];
  int i;
  boolean_T exitg1;
  double s;
  double ba;
  int hoffset;
  double d;
  double tst;
  double aa;
  double ab;
  double bb;
  double h22;
  double rt1r;
  int iy;
  info = 0;
  v[0] = 0.0;
  v[1] = 0.0;
  v[2] = 0.0;
  h[2] = 0.0;
  i = 2;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    int k;
    boolean_T goto150;
    int its;
    boolean_T exitg2;
    int b_i;
    int nr;
    int m;
    int b_k;
    k = -1;
    goto150 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      boolean_T exitg3;
      k = i - 1;
      exitg3 = false;
      while ((!exitg3) && (k + 2 > 1)) {
        b_i = k + 3 * k;
        ba = std::abs(h[b_i + 1]);
        if (ba <= 3.0062525400134592E-292) {
          exitg3 = true;
        } else {
          nr = 3 * (k + 1);
          hoffset = k + nr;
          iy = hoffset + 1;
          bb = std::abs(h[iy]);
          tst = std::abs(h[b_i]) + bb;
          if (tst == 0.0) {
            if (k >= 1) {
              tst = std::abs(h[k + 3 * (k - 1)]);
            }

            if (k + 3 <= 3) {
              tst += std::abs(h[nr + 2]);
            }
          }

          if (ba <= 2.2204460492503131E-16 * tst) {
            tst = std::abs(h[hoffset]);
            if (ba > tst) {
              ab = ba;
              ba = tst;
            } else {
              ab = tst;
            }

            tst = std::abs(h[b_i] - h[iy]);
            if (bb > tst) {
              aa = bb;
              bb = tst;
            } else {
              aa = tst;
            }

            s = aa + ab;
            tst = 2.2204460492503131E-16 * (bb * (aa / s));
            if ((3.0062525400134592E-292 > tst) || rtIsNaN(tst)) {
              tst = 3.0062525400134592E-292;
            }

            if (ba * (ab / s) <= tst) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }

      if (k + 2 > 1) {
        h[(k + 3 * k) + 1] = 0.0;
      }

      if (k + 2 >= i) {
        goto150 = true;
        exitg2 = true;
      } else {
        if (its == 10) {
          s = std::abs(h[1]) + std::abs(h[5]);
          tst = 0.75 * s + h[0];
          ab = -0.4375 * s;
          aa = s;
          h22 = tst;
        } else if (its == 20) {
          s = std::abs(h[i + 3 * (i - 1)]) + std::abs(h[i - 1]);
          tst = 0.75 * s + h[i + 3 * i];
          ab = -0.4375 * s;
          aa = s;
          h22 = tst;
        } else {
          nr = i + 3 * (i - 1);
          tst = h[nr - 1];
          aa = h[nr];
          ab = h[(i + 3 * i) - 1];
          h22 = h[i + 3 * i];
        }

        s = ((std::abs(tst) + std::abs(ab)) + std::abs(aa)) + std::abs(h22);
        if (s == 0.0) {
          rt1r = 0.0;
          tst = 0.0;
          ba = 0.0;
          aa = 0.0;
        } else {
          tst /= s;
          aa /= s;
          ab /= s;
          h22 /= s;
          bb = (tst + h22) / 2.0;
          tst = (tst - bb) * (h22 - bb) - ab * aa;
          aa = std::sqrt(std::abs(tst));
          if (tst >= 0.0) {
            rt1r = bb * s;
            ba = rt1r;
            tst = aa * s;
            aa = -tst;
          } else {
            rt1r = bb + aa;
            ba = bb - aa;
            if (std::abs(rt1r - h22) <= std::abs(ba - h22)) {
              rt1r *= s;
              ba = rt1r;
            } else {
              ba *= s;
              rt1r = ba;
            }

            tst = 0.0;
            aa = 0.0;
          }
        }

        m = i - 1;
        if (i - 1 >= 1) {
          ab = h[0] - ba;
          s = (std::abs(ab) + std::abs(aa)) + std::abs(h[1]);
          bb = h[1] / s;
          v[0] = (bb * h[3] + (h[0] - rt1r) * (ab / s)) - tst * (aa / s);
          v[1] = bb * (((h[0] + h[4]) - rt1r) - ba);
          v[2] = bb * h[5];
          s = (std::abs(v[0]) + std::abs(v[1])) + std::abs(v[2]);
          v[0] /= s;
          v[1] /= s;
          v[2] /= s;
        }

        for (b_k = m; b_k <= i; b_k++) {
          int j;
          nr = (i - b_k) + 2;
          if (3 < nr) {
            nr = 3;
          }

          if (b_k > i - 1) {
            hoffset = (b_k + 3 * (b_k - 2)) - 1;
            for (j = 0; j < nr; j++) {
              v[j] = h[j + hoffset];
            }
          }

          tst = v[0];
          bb = xzlarfg(nr, &tst, v);
          v[0] = tst;
          if (b_k > i - 1) {
            h[b_k - 1] = tst;
            h[b_k] = 0.0;
            if (b_k < i) {
              h[2] = 0.0;
            }
          }

          s = v[1];
          tst = bb * v[1];
          if (nr == 3) {
            d = v[2];
            ab = bb * v[2];
            for (j = b_k; j < 4; j++) {
              iy = 3 * (j - 1);
              nr = b_k + iy;
              hoffset = nr - 1;
              aa = (h[hoffset] + s * h[nr]) + d * h[nr + 1];
              h[hoffset] -= aa * bb;
              h[nr] -= aa * tst;
              b_i = iy + 2;
              h[b_i] -= aa * ab;
            }

            if (b_k + 3 < i + 1) {
              b_i = b_k + 2;
            } else {
              b_i = i;
            }

            for (j = 0; j <= b_i; j++) {
              nr = j + 3 * (b_k - 1);
              hoffset = j + 3 * b_k;
              aa = (h[nr] + s * h[hoffset]) + d * h[j + 3 * (b_k + 1)];
              h[nr] -= aa * bb;
              h[hoffset] -= aa * tst;
              h[j + 6] -= aa * ab;
            }

            for (j = 0; j < 3; j++) {
              nr = j + 3 * (b_k - 1);
              hoffset = j + 3 * b_k;
              aa = (z[nr] + s * z[hoffset]) + d * z[j + 3 * (b_k + 1)];
              z[nr] -= aa * bb;
              z[hoffset] -= aa * tst;
              z[j + 6] -= aa * ab;
            }
          } else {
            if (nr == 2) {
              for (j = b_k; j < 4; j++) {
                nr = b_k + 3 * (j - 1);
                hoffset = nr - 1;
                aa = h[hoffset] + s * h[nr];
                h[hoffset] -= aa * bb;
                h[nr] -= aa * tst;
              }

              for (j = 0; j <= i; j++) {
                nr = j + 3 * (b_k - 1);
                hoffset = j + 3 * b_k;
                aa = h[nr] + s * h[hoffset];
                h[nr] -= aa * bb;
                h[hoffset] -= aa * tst;
              }

              for (j = 0; j < 3; j++) {
                nr = j + 3 * (b_k - 1);
                hoffset = j + 3 * b_k;
                aa = z[nr] + s * z[hoffset];
                z[nr] -= aa * bb;
                z[hoffset] -= aa * tst;
              }
            }
          }
        }

        its++;
      }
    }

    if (!goto150) {
      info = i + 1;
      exitg1 = true;
    } else {
      if ((k + 2 != i + 1) && (k + 2 == i)) {
        b_i = i + 3 * i;
        nr = b_i - 1;
        s = h[nr];
        m = 3 * (i - 1);
        hoffset = i + m;
        d = h[hoffset];
        tst = h[b_i];
        xdlanv2(&h[(i + 3 * (i - 1)) - 1], &s, &d, &tst, &aa, &ab, &bb, &ba,
                &h22, &rt1r);
        h[nr] = s;
        h[hoffset] = d;
        h[b_i] = tst;
        if (3 > i + 1) {
          nr = 1 - i;
          iy = i + (i + 1) * 3;
          hoffset = iy - 1;
          for (b_k = 0; b_k <= nr; b_k++) {
            tst = h22 * h[hoffset] + rt1r * h[iy];
            h[iy] = h22 * h[iy] - rt1r * h[hoffset];
            h[hoffset] = tst;
            iy += 3;
            hoffset += 3;
          }
        }

        nr = i * 3;
        if (i - 1 >= 1) {
          tst = h22 * h[m] + rt1r * h[nr];
          h[nr] = h22 * h[nr] - rt1r * h[m];
          h[m] = tst;
        }

        tst = h22 * z[m] + rt1r * z[nr];
        z[nr] = h22 * z[nr] - rt1r * z[m];
        z[m] = tst;
        iy = nr + 1;
        hoffset = m + 1;
        tst = h22 * z[hoffset] + rt1r * z[iy];
        z[iy] = h22 * z[iy] - rt1r * z[hoffset];
        z[hoffset] = tst;
        iy++;
        hoffset++;
        tst = h22 * z[hoffset] + rt1r * z[iy];
        z[iy] = h22 * z[iy] - rt1r * z[hoffset];
        z[hoffset] = tst;
      }

      i = k;
    }
  }

  return info;
}

//
// File trailer for xhseqr.cpp
//
// [EOF]
//
