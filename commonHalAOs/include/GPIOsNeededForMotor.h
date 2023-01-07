#pragma once
 

#include "AEGPIOOutput.h"

class GPIOsNeededForMotor
{
	
	AEGPIOOutput* IN1;
	AEGPIOOutput* IN2;

public:
	
	GPIOsNeededForMotor(AEGPIOOutput* iN1, AEGPIOOutput* iN2)
		: IN1(iN1), IN2(iN2)
	{}

};