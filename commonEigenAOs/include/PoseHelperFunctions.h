#pragma once


//#include <armadillo\src\Geometry\Quaternion.h>

//#include "Mex_Angle2QuatFunc.h"


class PoseHelperFunctions
{
public:
	PoseHelperFunctions() {};


	/*
	void AngleToQuaternion(double yaw, double pitch, double roll, double* Q) // yaw (Z), pitch (Y), roll (X)
	{
		// Abbreviations for the various angular functions
		double cy = cos(yaw * 0.5);
		double sy = sin(yaw * 0.5);
		double cp = cos(pitch * 0.5);
		double sp = sin(pitch * 0.5);
		double cr = cos(roll * 0.5);
		double sr = sin(roll * 0.5);
		 
		Q[0] = cr * cp * cy + sr * sp * sy;
		Q[1] = sr * cp * cy - cr * sp * sy;
		Q[2] = cr * sp * cy + sr * cp * sy;
		Q[3] = cr * cp * sy - sr * sp * cy;
		 
	}*/

 
	/*static Eigen::Quaternionf AngleToQuaternion(double currentYaw, double currentPitch, double currentRoll)
	{
		double Q1[4];
		Mex_Angle2QuatFunc(currentYaw, currentPitch, currentRoll, Q1);
		Eigen::Quaternionf Qdelgyro(Q1[0], Q1[1], Q1[2], Q1[3]);
		return Qdelgyro;
	}*/


	/// this only works for a ZYX Rotation sequence with the q[4] of form q = [x y z w]
	static void QuatToEulerAngles(float* yaw, float* pitch, float* roll, float* q) { 
		/*
	  // roll [1]-[1]is rotation)
	  double sinr_cosp = 2 * (q[4] * q[1] + q[2] * q[3]);
	  double cosr_cosp = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);
	  *roll = std::atan2(sinr_cosp, cosr_cosp);

	  // pitch (y-[1]is rotation)
	  double sinp = 2 * (q[0] * q[2] - q[3] * q[1]);
	  if (std::abs(sinp) >= 1)
		  *pitch = std::copysign(3.141592653589 / 2, sinp); // use 90 degrees if out of range
	  else
		  *pitch = std::asin(sinp);

	  // yaw (z-[1]is rotation)
	  double siny_cosp = 2 * (q[0] * q[3] + q[1] * q[2]);
	  double cosy_cosp = 1 - 2 * (q[2] * q[2] + q[3] * q[3]);
	  *yaw = std::atan2(siny_cosp, cosy_cosp);
	   */
	   /*
		testquat q1;
		q1.x = q[3];
		q1.y = q[0];
		q1.z = q[1];
		q1.w = q[2];
		double heading  =(double)*yaw;
		  double attitude = (double)*pitch;
		  double bank = (double)*roll;

   double test = q1.x*q1.y + q1.z*q1.w;
   if (test > 0.499) { // singularity at north pole
	   heading = 2 * atan2(q1.x,q1.w);
	   attitude = 3.14159265359 /2;
	   bank = 0;
	   return;
   }
   if (test < -0.499) { // singularity at south pole
	   heading = -2 * atan2(q1.x,q1.w);
	   attitude = -3.14159265359 /2;
	   bank = 0;
	   return;
   }
   double sqx = q1.x*q1.x;
   double sqy = q1.y*q1.y;
   double sqz = q1.z*q1.z;
   heading = atan2(2*q1.y*q1.w-2*q1.x*q1.z , 1 - 2*sqy - 2*sqz);
   attitude = asin(2*test);
   bank = atan2(2 * q1.x*q1.w - 2 * q1.y*q1.z, 1 - 2 * sqx - 2 * sqz);

   *yaw = (float)heading;
   *pitch = (float)attitude;
   *roll = (float)bank; */

		float qin1 = q[3];
		float qin2 = q[0];
		float qin3 = q[1];
		float qin4 = q[2];

		float r11 = 2 * ((qin2*qin3) + (qin1*qin4));
		float r12 = qin1 * qin1 + qin2 * qin2 - qin3 * qin3 - qin4 * qin4;
		float r21 = -2 * ((qin2*qin4) - (qin1*qin3));
		float r31 = 2 * ((qin3*qin4) + (qin1*qin2));
		float r32 = qin1 * qin1 - qin2 * qin2 - qin3 * qin3 + qin4 * qin4;

		*yaw = atan2(r11, r12);
		r21 = (r21 < -1) ? -1 : r21;
		r21 = (r21 > 1) ? 1 : r21;
		*pitch = asin(r21);
		*roll = atan2(r31, r32);
	}

	static void AverageQuaternions(float* Q1, float weight1, float* Q2, float weight2, float* Q3)
	{

		float  Qsimilar = SiliarityOfQuaternions(Q1, Q2);
		if (Qsimilar < 0)
		{
			Q1[0] = -Q1[0];
			Q1[1] = -Q1[1];
			Q1[2] = -Q1[2];
			Q1[3] = -Q1[3]; 
		}
		 
		Q3[0] =	((weight1*Q1[0]) + (weight2*Q2[0]));
		Q3[1] =	((weight1*Q1[1]) + (weight2*Q2[1]));
		Q3[2] =	((weight1*Q1[2]) + (weight2*Q2[2]));
		Q3[3] =	((weight1*Q1[3]) + (weight2*Q2[3]));


	}

	static float SiliarityOfQuaternions(float* Q1, float* Q2)
	{ 
		float Qsimilar = (Q1[0]* Q2[0]) + (Q1[1]* Q2[1]) + (Q1[2] * Q2[2]) + (Q1[3] * Q2[3]);
		return Qsimilar;
	}

	static double AverageAngles(float angle1, float weight1, float angle2, float
		weight2)
	{
		float newAngle;
		bool guard1 = false;
		float smallestAngle;
		float largerAngle;
		float Sweight;
		float Lweight;

		// get the smallest angle
		guard1 = false;
		if (angle1 < angle2) {
			smallestAngle = angle1;
			largerAngle = angle2;
			Sweight = weight1;
			Lweight = weight2;
			guard1 = true;
		}
		else if (angle2 < angle1) {
			smallestAngle = angle2;
			largerAngle = angle1;
			Sweight = weight2;
			Lweight = weight1;
			guard1 = true;
		}
		else {
			newAngle = angle1;
		}

		if (guard1) {
			// if the largerAngle - smallestAngle is less than 180 than just do a normal 
			// averaging, otherwise th angles must wrap to the right side past zero
			if (largerAngle - smallestAngle <= 3.1415926535897931) {
				newAngle = angle1 * weight1 + angle2 * weight2;
			}
			else {
				// convert larger angle to a negative on the unit circle
				largerAngle -= 6.2831853071795862;
				newAngle = smallestAngle * Sweight + largerAngle * Lweight;
			}

			// if new angle became negative, convert it back to positive on the unit
			// circle
			if (newAngle < 0.0) {
				newAngle += 6.2831853071795862;
			}
		}

		return newAngle;
	}


private:

};

