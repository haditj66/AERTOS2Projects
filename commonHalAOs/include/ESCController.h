#pragma once

#include "AEUtils.h"

#include "AEPWM.h"

enum ESCTypeEnum
{
	Black40AChineseESC
};

 
class ESCController
{
public:
	AEPWM* PWMToUse;

	ESCController(ESCTypeEnum ESCType, AEPWM* PWMToUse);

	void changeSpeed(float speedFrom0To100);
	void InitializeESC();

private:
	float minDutyCycle;
	float maxDutyCycle;
	ESCTypeEnum ESCType;

};
 
inline ESCController::ESCController(ESCTypeEnum ESCType, AEPWM* PWMToUse)
{
	this->PWMToUse = PWMToUse;
	this->ESCType = ESCType;
	if (ESCType == Black40AChineseESC)
	{
		//22.3 hz// 300 mv  // 5.3 ? 
		minDutyCycle = 5.12;//2.95;
		maxDutyCycle = 8.75;//3.9;
	}

}
 
inline void ESCController::changeSpeed(float speedFrom0To100)
{
	float mappedVAl = AE_Map(speedFrom0To100, 0, 100, minDutyCycle, maxDutyCycle);

	PWMToUse->ChangeDutyCycle(mappedVAl);

}
 
inline void ESCController::InitializeESC()
{

	PWMToUse->StartPWM();

	if (this->ESCType == Black40AChineseESC)
	{
		PWMToUse->ChangeDutyCycle(minDutyCycle);
	}
	else
	{
		PWMToUse->ChangeDutyCycle(minDutyCycle);
	}


}

