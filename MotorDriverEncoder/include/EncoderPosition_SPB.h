//generated file: C:/Users/hadi/Documents/AERTOSProjects/MotorDriverEncoder\include\EncoderPosition_SPB.h
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.

//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################

#pragma once


#include "AESPBObservorOutputType.h"
#include "AEUtils.h"
#include "FreeRTOS.h"
#include "AEFilter.h"

#include "AEIntegrationTesting.h"

//UserCode_Sectionheader

#include "EncoderStateEnum.h"
//UserCode_Sectionheader_end

template<bool isSubscribable, TEMPLATESPB_Filters>
	class EncoderPosition_SPB :
		public AESPBObservorOutputType <1, 2, isSubscribable,
TEMPLATESPB_FilterParams,
1, false,
1, false>
	{
	public:
		EncoderPosition_SPB();
		
		//UserCode_Sectionpublic
//UserCode_Sectionpublic_end


	protected: int16_t currentPosition; 
public: int16_t  GetcurrentPosition()   const {return currentPosition; }

protected: bool reverseCount; 
public: bool  GetreverseCount()   const {return reverseCount; }


public: void UserInitialize(int16_t _currentPosition , bool _reverseCount  = false)
	{
		currentPosition =  _currentPosition;
reverseCount =  _reverseCount;

		
		//UserCode_SectionuserInited
		firstUpdateMade = false;
//UserCode_SectionuserInited_end
		
		userInitialized = true;
	}
private: bool userInitialized = false;
protected: void CheckIfConfiguredProperly() const override  
	{
		//EncoderPosition_SPB::CheckIfConfiguredProperly();
		if (userInitialized == false)
		{
			// you did not initialize one of your AEobjects
			AEAssertRuntime(userInitialized == true, "user did not call the UserInitailize function for  EncoderPosition_SPB"); 
		} 
		 
	}
	
	private:
	//UserCode_Sectionprivate
		bool OpticalSensorState1; 
		bool OpticalSensorState2;
		bool firstUpdateMade;
		EncoderStateEnum encoderState;
		
		EncoderStateEnum GetEncoderState(bool opticalSensor1, bool opticalSensor2) const;
		int8_t GetPositionDifference(EncoderStateEnum EncoderState1, EncoderStateEnum EncoderState2);
		
//UserCode_Sectionprivate_end

		void RefreshOVERRIDE(float OutputSignal[1]) override;

	};


//UserCode_Sectionfunc

template<bool isSubscribable, TEMPLATESPB_FiltersFunctionParams>
	inline EncoderStateEnum EncoderPosition_SPB<  isSubscribable, TEMPLATESPB_FilterParams>
	::GetEncoderState(bool opticalSensor1, bool opticalSensor2) const
	{
		return (EncoderStateEnum)((opticalSensor1 << 1) | opticalSensor2);

	}

template<bool isSubscribable, TEMPLATESPB_FiltersFunctionParams>
	inline int8_t EncoderPosition_SPB<  isSubscribable, TEMPLATESPB_FilterParams>
	::GetPositionDifference(EncoderStateEnum EncoderState1, EncoderStateEnum EncoderState2)
	{

		//00
		if (EncoderState1 == EncoderStateEnum::ZeroZero)
		{
			if (EncoderState2 == EncoderStateEnum::OneZero)
			{
				return reverseCount == true ? -1 : 1;
			}
			else if (EncoderState2 == EncoderStateEnum::ZeroOne)
			{
				return reverseCount == true ? 1 : -1;
			}
			else
			{
				//the motor must have turned so fast that it skipped a count 
				configASSERT(false);
			}
		}

		//01
		if (EncoderState1 == EncoderStateEnum::ZeroOne)
		{
			if (EncoderState2 == EncoderStateEnum::ZeroZero)
			{
				return reverseCount == true ? -1 : 1;
			}
			else if (EncoderState2 == EncoderStateEnum::OneOne)
			{
				return reverseCount == true ?  1 : -1;
			}
			else
			{
				//the motor must have turned so fast that it skipped a count 
				configASSERT(false);
			}
		}

		//11
		if (EncoderState1 == EncoderStateEnum::OneOne)
		{
			if (EncoderState2 == EncoderStateEnum::ZeroOne)
			{
				return reverseCount == true ? -1 : 1;
			}
			else if (EncoderState2 == EncoderStateEnum::OneZero)
			{
				return reverseCount == true ?  1 : -1;
			}
			else
			{
				//the motor must have turned so fast that it skipped a count 
				configASSERT(false);
			}
		}
		//10
		if (EncoderState1 == EncoderStateEnum::OneZero)
		{
			if (EncoderState2 == EncoderStateEnum::OneOne)
			{
				return reverseCount == true ? -1 : 1;
			}
			else if (EncoderState2 == EncoderStateEnum::ZeroZero)
			{
				return reverseCount == true ? 1 : -1;
			}
			else
			{
				//the motor must have turned so fast that it skipped a count 
				configASSERT(false);
			}
		}
        
		//the motor must have turned so fast that it skipped a count 
		configASSERT(false);
	}

//UserCode_Sectionfunc_end


template<bool isSubscribable, TEMPLATESPB_FiltersFunctionParams>
	inline EncoderPosition_SPB< isSubscribable, TEMPLATESPB_FilterParams>::EncoderPosition_SPB()
	{
		//UserCode_Sectionctor
//UserCode_Sectionctor_end
	}

template<bool isSubscribable, TEMPLATESPB_FiltersFunctionParams>
	inline void EncoderPosition_SPB< isSubscribable, TEMPLATESPB_FilterParams>::RefreshOVERRIDE(float OutputSignal[1])
	{

		float* ch1 = this->InputChannels[0]->ChannelSignalBufferSingle; 
float* ch2 = this->InputChannels[1]->ChannelSignalBufferSingle; 

 
		//UserCode_Sectionrefresh
		if (firstUpdateMade == false)
		{
			//if no update has been made yet, then just set the opticalsensors state
			OpticalSensorState1 = *ch1 >=.999;
			OpticalSensorState2 = *ch2 >=.999;
			encoderState = GetEncoderState(OpticalSensorState1, OpticalSensorState2);
			firstUpdateMade = true;
                 
			OutputSignal[0] = currentPosition;
			return;
		}
		else
		{
			//if there was a change in a sensor state, then change current position
			bool newOpticalState1 = *ch1 >=.999;
			bool newOpticalState2 = *ch2 >=.999;
			EncoderStateEnum newEncoderState = GetEncoderState(newOpticalState1, newOpticalState2);

			if (newEncoderState != encoderState)
			{

				int8_t posDiff = GetPositionDifference(newEncoderState, encoderState);
				currentPosition += posDiff;
				encoderState = GetEncoderState(newOpticalState1, newOpticalState2);

				/*
				//if is is not the same then incrmement the current position based on if it was going clockwiseOrAnitclockwise
				if (MotorDriver->GetMotorState() == MotorState::TurningAntiClockwise)
				{
					CurrentPosition--;
					IsHallSensorHigh = newHallState;
				}
				else if (MotorDriver->GetMotorState() == MotorState::TurningClockwise)
				{
					CurrentPosition++;
					IsHallSensorHigh = newHallState;
				}*/
                         
				OutputSignal[0] = currentPosition;
				return;
			}
			else
			{
				OutputSignal[0] = currentPosition;
				return;
			}
		}

		OutputSignal[0] = currentPosition;
//UserCode_Sectionrefresh_end
	}

