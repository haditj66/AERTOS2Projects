#pragma once

#include <Dense> 


#define AngleToQuat_M(Yaw,Pitch,Roll, nameOfQuat) double Q1##nameOfQuat[4];\
 Mex_Angle2QuatFunc(Yaw, Pitch, Roll, Q1##nameOfQuat); Eigen::Quaternionf\
  nameOfQuat (Q1##nameOfQuat[0], Q1##nameOfQuat[1], Q1##nameOfQuat[2], Q1##nameOfQuat[3]);

class ComplFilter
{
public:
	float currentRoll;
	float currentPitch;
	float currentYaw;
	float SampleDeltaTime;
	float FilterConstantForGyro;
	Eigen::Quaternionf CurrentQuat;

	ComplFilter(float samplingFrequency, float filterConstantForGyro)
	{
		FilterConstantForGyro = filterConstantForGyro;
		SampleDeltaTime = 1 / samplingFrequency;
		firstUpdate = true;
	}


	void OrientationFromAccelMag(Eigen::Vector3d* accel, Eigen::Vector3d* mag, float * Roll, float * Pitch, float * Yaw);
	void UpdateOrientation(Eigen::Vector3d* accel, Eigen::Vector3d* gyro, Eigen::Vector3d* mag, float * Roll, float * Pitch, float * Yaw);

protected:
	bool firstUpdate;
};

