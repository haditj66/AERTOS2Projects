//generated file: C:/Users/hadi/Documents/AERTOSProjects/MotorDriverEncoder\conf\AEConfig.h
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.

//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################

#pragma once 
 
 
#ifdef  BOARD_USED__STM32F411RE
#include "stm32f4xx_hal.h"
#endif //  BOARD_USED__STM32F411RE

//UserCode_Sectiondefines
//UserCode_Sectiondefines_end







//####################################
//AE Settings
//####################################

#define AEconfigTICK_RATE_HZ 1000
#define AEconfigMINIMAL_STACK_SIZE 928
#define AEconfigTIMER_TASK_STACK_DEPTH 1500
#define AEconfigTOTAL_HEAP_SIZE 75000
#define AOPRIORITYLOWEST 5
#define AOPRIORITYMEDIUM 10
#define AOPRIORITYHIGHEST 29
#define NUMOFACTIVEOBJECTS 8
#define HIGHEST_NUM_OF_EVT_INSTANCES 2
#define MAX_OUTPUT_SIZE_OF_SPB_SET_TO_TDU 1
#define NUM_OF_TDUS_THAT_FLOW_FROM_SPBS 1
#define MAXSPB_CHAIN_POOLSIZE 5
#define MAXNUMOFINTERPRETORS 3
#define MAXNUMOFOBSERVERINFLUENCES 2
#define MAXNUMOFOBSERVORS 6
#define MAXNUMOFSENSORS 3
#define MAXNUMBEROF_FILTERS 1
#define MAXNUMBEROF_FILTERS_From_A_Sensor 1
#define MaxNumOfAELoops 3
#define MAXNUMBEROFINPUTSIGNALS_TO_A_SPB 2
#define MAXNUMBEROFOUTPUTSIGNALS_TO_A_SPB 2
#define MAXNUM_OF_SUBSCRIBERS_To_A_SPB 1
#define MAXNUM_OF_AE_SUBSCRIPTIONS_To_SPBs 1
#define TOTALMAXNUMBEROFOUTPUTSIGNALS_TO_ALL_SPBs 10
#define MAXNUMOFTDUSSETTOTheSameSPB 3
#define configAE_USE_TDUs_AsService 1
#define configAE_USE_U_AsService 1
#define configAE_USE_DDSM_AsService 0
#define DontCheckForHardDeadlinesInSPBsForEverySetInput
#define AEDontCheckForCorrectActionRequestTemplate
#define Target_stm32f4








//####################################
//AO defines
//####################################

#define ADCPERIPHERAL1 ADCPeripheral<1, PortB, PIN0, PortA, PIN2> 
#define ADCPERIPHERAL1_Name_CH1 ADCPERIPHERAL_inst1_ch1
#define ADCPERIPHERAL1_Name_CH2 ADCPERIPHERAL_inst1_ch2


#define PWMPERIPHERAL1 PWMPeripheral<1, PortD, PIN12> 
#define PWMPERIPHERAL1_Name PWMPERIPHERAL_inst1

#define GPIOPERIPHERAL1 GPIOPeripheral< PortB, PIN7> 
#define GPIOPERIPHERAL1_Name GPIOPERIPHERAL_inst1

#define AOInclude1 MotorDriverSpeedControllerTDU
#define TemplateToAO1 
#define ClassNameOfAO1 MotorDriverSpeedControllerTDU
#define TypeOfAO1_1 MotorDriverSpeedControllerTDU
#define InstanceNameOfAO1_1 motorDriverSpeedControllerTDU


#define ClockType1 AEClock<AEObservorSensor, AEObservorInterpretorBaseDUMMY, 2, 0, 0, 0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0> 
#define ClockName1 clock1 

#define SensorName1 opticalsensor1

#define SensorName2 opticalsensor2

#define AOInclude2 EncoderPosition_SPB
#define TemplateToAO2 template<bool isSubscribable, TEMPLATESPB_Filters>
#define ClassNameOfAO2 EncoderPosition_SPB
#define TypeOfAO2_1 EncoderPosition_SPB< true,  1, Filter<AngularDerivativeDiscreteFilter<20, 10 >, 2>>
#define InstanceNameOfAO2_1 encoderPosition_SPB

#define AOInclude3 PID_SPB
#define TemplateToAO3 template<bool isSubscribable, uint32_t CHANNEL_CONSUMPTION_SIZE1, TEMPLATESPB_Filters>
#define ClassNameOfAO3 PID_SPB
#define TypeOfAO3_1 PID_SPB< true,  1>
#define InstanceNameOfAO3_1 angularPositionPID

#define AOInclude4 PID_WithDesiredInputAsChannel_SPB
#define TemplateToAO4 template<bool isSubscribable, TEMPLATESPB_Filters>
#define ClassNameOfAO4 PID_WithDesiredInputAsChannel_SPB
#define TypeOfAO4_1 PID_WithDesiredInputAsChannel_SPB< true>
#define InstanceNameOfAO4_1 angularVelocityPID

#define AnyOtherNeededIncludes1 HighOrLowFilter 


#define AnyOtherNeededIncludes2 AngularDerivativeDiscreteFilter 


#define Event1 DummyEVT
#define Event1Size 10




//####################################
//AE hal defines
//####################################


