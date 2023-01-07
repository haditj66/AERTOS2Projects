//
// File: Mex_Angle2QuatFunc.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 21-Jun-2020 14:58:51
//

// Include Files
#include "Mex_Angle2QuatFunc.h"
#include <cmath>
#include "AEUtils.h"
#include "AEFastTrig.h"


// Function Definitions

//
// Q = angle2quat(currentYaw, currentPitch, currentRoll, 'ZYX');
// Arguments    : double currentYaw
//                double currentPitch
//                double currentRoll
//                double Q[4]
// Return Type  : void
//
void Mex_Angle2QuatFunc(double currentYaw, double currentPitch, double
	currentRoll, double Q[4])
{

	float c_idx_0;
	float s_idx_0;
	float c_idx_1;
	float s_idx_1;
	float c_idx_2;
	float s_idx_2;
	float Q_tmp;
	float b_Q_tmp;
	//TimeForEnteringAndReenteringAndPrintAll(2)
	c_idx_0 = AE::cos(currentYaw / 2.0);
	s_idx_0 = AE::sin(currentYaw / 2.0);
	c_idx_1 = AE::cos(currentPitch / 2.0);
	s_idx_1 = AE::sin(currentPitch / 2.0);
	c_idx_2 = AE::cos(currentRoll / 2.0);
	s_idx_2 = AE::sin(currentRoll / 2.0);
	//TimeForEnteringAndReenteringAndPrintAll(2) //1ms
	Q_tmp = c_idx_0 * c_idx_1;
	b_Q_tmp = s_idx_0 * s_idx_1;
	Q[0] = Q_tmp * c_idx_2 + b_Q_tmp * s_idx_2;
	Q[1] = Q_tmp * s_idx_2 - b_Q_tmp * c_idx_2;
	Q_tmp = s_idx_0 * c_idx_1;
	b_Q_tmp = c_idx_0 * s_idx_1;
	Q[2] = b_Q_tmp * c_idx_2 + Q_tmp * s_idx_2;
	Q[3] = Q_tmp * c_idx_2 - b_Q_tmp * s_idx_2;
}

/*
Eigen::Quaternionf Mex_Angle2QuatFunc(double currentYaw, double currentPitch, double currentRoll)
{
	double Q1[4];
	Mex_Angle2QuatFunc(currentYaw, currentPitch, currentRoll, Q1);
	static Eigen::Quaternionf Qdelgyro(Q1[0], Q1[1], Q1[2], Q1[3]);
	return Qdelgyro;
}
*/


//
// Arguments    : void
// Return Type  : void
//
void Mex_Angle2QuatFunc_initialize()
{
}

//
// Arguments    : void
// Return Type  : void
//
void Mex_Angle2QuatFunc_terminate()
{
  // (no terminate code required)
}

//
// File trailer for Mex_Angle2QuatFunc.cpp
//
// [EOF]
//
