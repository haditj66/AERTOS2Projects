#include "ComplFilter.h"

#include "Mex_DCM2AngleFunc.h"

#include "PoseHelperFunctions.h"
#include "Mex_Angle2QuatFunc.h"

#include <Geometry>
#include "AEUtils.h"
void ComplFilter::OrientationFromAccelMag(Eigen::Vector3d* accel, Eigen::Vector3d* mag, float * Roll, float* Pitch, float* Yaw)
{


	//z-y'-x''
//   N                                               E                                                      D
// cos(psi) cos(thet)                                 sin(psi)cos(thet)                                -sin(thet)
// cos(psi)sin(thet)sin(phi)-sin(psi)cos(phi)       sin(psi)sin(thet)sin(phi)+cos(psi)cos(phi)       cos(thet)sin(phi)
// sin(phi)sin(psi) + cos(phi)sin(thet)cos(psi)     -sin(phi)cos(psi) + cos(phi)sin(thet)sin(psi)    cos(thet)cos(phi)





	//get down vector
	//Eigen::Vector3d accel_unit(accel);
	accel->normalize();

	//get mag vector
	//Eigen::Vector3d mag_unit(mag);
	mag->normalize();

	//get east
	Eigen::Vector3d E;
	E = accel->cross(*mag);
	E.normalize();

	//get north
	Eigen::Vector3d N;
	N = E.cross(*accel);
	N.normalize();


	//build the dcm aka rotational matrix 
	Eigen::Matrix<double, 3, 3> DCM_;
	DCM_.block<1, 3>(0, 0) = N;
	DCM_.block<1, 3>(1, 0) = E;
	DCM_.block<1, 3>(2, 0) = *accel;
	//TimeForEnteringAndReenteringAndPrintAll(2) //A
	Eigen::Matrix<double, 3, 3> dfd = DCM_.inverse();
	//TimeForEnteringAndReenteringAndPrintAll(2) //A .34 ms



			//TimeForEnteringAndReenteringAndPrintAll(2) //B
	Mex_DCM2AngleFunc(dfd.data(), Yaw, Pitch, Roll);
	//TimeForEnteringAndReenteringAndPrintAll(2) //B .284 ms


}


float const pi = 3.14159265359;




void ComplFilter::UpdateOrientation(Eigen::Vector3d * accel, Eigen::Vector3d * gyro, Eigen::Vector3d * mag, float * Roll, float * Pitch, float * Yaw)
{

	if (this->firstUpdate == false)
	{


		//get quaternion from gyro
		float gyroRoll = (((*gyro)(0)) * this->SampleDeltaTime);
		float gyroPitch = (((*gyro)(1)) * this->SampleDeltaTime);
		float gyroYaw = (((*gyro)(2)) * this->SampleDeltaTime);

		AngleToQuat_M(gyroYaw, gyroPitch, gyroRoll, Qdelgyro)
			Eigen::Quaternionf Qnew = CurrentQuat * Qdelgyro;



		//get what the accel and mag  orientation 
		float accelmagRoll;
		float accelmagPitch;
		float accelmagYaw;
		//TimeForEnteringAndReenteringAndPrintAll(2)//B
		this->OrientationFromAccelMag(accel, mag, &accelmagRoll, &accelmagPitch, &accelmagYaw);
		//TimeForEnteringAndReenteringAndPrintAll(2)B // .998 ms

		//TimeForEnteringAndReenteringAndPrintAll(2) //A 
		AngleToQuat_M(accelmagYaw, accelmagPitch, accelmagRoll, Qaccel)
			//TimeForEnteringAndReenteringAndPrintAll(2) //A .083 ms





	//getting averaging weight constants
			float filtConst2 = 1 - this->FilterConstantForGyro;

		float trustOfAccelMag = 1;
		float pitchangleToCheck = this->currentPitch < 0 ? (this->currentPitch + (pi * 2)) : this->currentPitch;
		if ((pitchangleToCheck > ((1.57) - .2) && pitchangleToCheck < ((1.57) + .2)) || (pitchangleToCheck > ((3 * 1.57) - .2) && pitchangleToCheck < ((3 * 1.57) + .2)))
		{

			trustOfAccelMag = .1;
		}
		else if ((pitchangleToCheck > ((1.57) - .5) && pitchangleToCheck < ((1.57) + .5)) || (pitchangleToCheck > ((3 * 1.57) - .5) && pitchangleToCheck < ((3 * 1.57) + .5)))
		{
			trustOfAccelMag = .7;
		}

		float newfiltConst2 = filtConst2 * trustOfAccelMag;
		float newFilterConstantForGyro = this->FilterConstantForGyro + (filtConst2 - newfiltConst2);



		// averaging quaternions    
		float Q[4];
		PoseHelperFunctions::AverageQuaternions(Qaccel.coeffs().data(), newfiltConst2, Qnew.coeffs().data(), newFilterConstantForGyro, Q);



		//update current angles and quaternion values.
		PoseHelperFunctions::QuatToEulerAngles(&currentYaw, &currentPitch, &currentRoll, Q);
		*Roll = currentRoll; *Pitch = currentPitch; *Yaw = currentYaw;
		Eigen::Quaternionf CurrentQuatL(Q[3], Q[0], Q[1], Q[2]);
		CurrentQuat = CurrentQuatL;

	}
	else
	{
		this->firstUpdate = false;
		this->OrientationFromAccelMag(accel, mag, &this->currentRoll, &this->currentPitch, &this->currentYaw);

		*Roll = currentRoll; *Pitch = currentPitch; *Yaw = currentYaw;

		double Q2[4] {0,0,0,0};
		Mex_Angle2QuatFunc(currentYaw, currentPitch, currentRoll, Q2);
		
		//for mingw compiler Eigen fails here. Dunno why but an assertion fails at  at line 68 file DenseStorage.h
		Eigen::Quaternionf CurrentQuatL(Q2[0], Q2[1], Q2[2], Q2[3]);
		CurrentQuat = CurrentQuatL;


	}
}
