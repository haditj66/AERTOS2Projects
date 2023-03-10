//generated file: C:/Users/hadi/Documents/AERTOSProjects/commonEigenAOs\conf\AEConfig.h
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
#define NUMOFACTIVEOBJECTS 11
#define HIGHEST_NUM_OF_EVT_INSTANCES 2
#define MAXSPB_CHAIN_POOLSIZE 5
#define MAXNUMOFINTERPRETORS 3
#define MAXNUMOFOBSERVERINFLUENCES 2
#define MAXNUMOFOBSERVORS 11
#define MAXNUMOFSENSORS 10
#define MAXNUMBEROF_FILTERS 1
#define MAXNUMBEROF_FILTERS_From_A_Sensor 0
#define MaxNumOfAELoops 3
#define MAXNUMBEROFINPUTSIGNALS_TO_A_SPB 9
#define MAXNUMBEROFOUTPUTSIGNALS_TO_A_SPB 1
#define MAXNUM_OF_SUBSCRIBERS_To_A_SPB 3
#define MAXNUM_OF_AE_SUBSCRIPTIONS_To_SPBs 3
#define TOTALMAXNUMBEROFOUTPUTSIGNALS_TO_ALL_SPBs 10
#define MAXNUMOFTDUSSETTOTheSameSPB 3
#define configAE_USE_TDUs_AsService 1
#define configAE_USE_U_AsService 1
#define configAE_USE_DDSM_AsService 0
#define DontCheckForHardDeadlinesInSPBsForEverySetInput
#define AEDontCheckForCorrectActionRequestTemplate
#define Target_stm32f4
#define SPB_OF_FILTER1_SUBSCRIBED








//####################################
//AO defines
//####################################

#define ClockType1 AEClock<AEObservorSensor, AEObservorInterpretorBaseDUMMY, 9, 0, 0, 0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0> 
#define ClockName1 clock1 

#define SensorName1 sens1

#define SensorName2 sens2

#define SensorName3 sens3

#define SensorName4 sens4

#define SensorName5 sens5

#define SensorName6 sens6

#define SensorName7 sens7

#define SensorName8 sens8

#define SensorName9 sens9

#define AOInclude1 PoseEulerAngles_SPB
#define TemplateToAO1 template<bool isSubscribable, TEMPLATESPB_Filters>
#define ClassNameOfAO1 PoseEulerAngles_SPB
#define TypeOfAO1_1 PoseEulerAngles_SPB< false>
#define InstanceNameOfAO1_1 poseEulerAngles_SPB

#define Event1 DummyEVT
#define Event1Size 10




//####################################
//AE hal defines
//####################################


