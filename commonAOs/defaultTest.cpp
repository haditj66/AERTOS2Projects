//generated file: C:/AERTOSProjects/commonAOs\defaultTest.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.

//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################


 
#if INTEGRATION_TESTS_FOR_commonAOs__defaultTest
 
#include "IntegTestPipeline.h"


#include "AECore.h"
#include "AE_Init.h" 
#include "AEClock.h" 
#include "AEObjects.h" 

DECLARE_ALL_AO_PTR

static void clock1_callback(TimerHandle_t xTimerHandle);
static int32_t sensor1_data[1];




//UserCode_Sectiona
//<20, 10 >
static Filter<AngularDerivativeDiscreteFilter<20,10>, 2>*  sensor1filt1;
//static  Filter<MovingAverageFilter<5>, 5>* sensor1filt2;
static  Filter<DerivativeFilter, 2>* sensor1filt2;

//UserCode_Sectiona_end

void RunSelectedIntegrationTest_defaultTest()
{

AE_Init();
 //UserCode_Sectionbeforemain
//UserCode_Sectionbeforemain_end


static AEClock<AEObservorSensor, AEObservorInterpretorBaseDUMMY, 1, 0, 0, 0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0> clock1L(1000, clock1_callback);
clock1 = &clock1L;

static AEObservorSensorFilterOut< 2, Filter<AngularDerivativeDiscreteFilter<20, 10 >, 2>,Filter<MovingAverageFilter, 5> ,1  > sensor1L((int32_t*) sensor1_data, SensorResolution::Resolution12Bit , 100 , 0);
sensor1 = &sensor1L;





static IfRightOnSPB< false> ifRightOnSPBL; ifRightOnSPBL.InitSPBObserver(StyleOfSPB::EachSPBTask); 
ifRightOnSPB = &ifRightOnSPBL;

static AverageSPB< false,  10> averageSPBL; averageSPBL.InitSPBObserver(StyleOfSPB::EachSPBTask); 
averageSPB = &averageSPBL;

static PID_SPB< false,  1> pidSPBL; pidSPBL.InitSPBObserver(StyleOfSPB::EachSPBTask); 
pidSPB = &pidSPBL;

static ThreeDimensionalVectorSPB< false> threeDimensionalVectorSPBL; threeDimensionalVectorSPBL.InitSPBObserver(StyleOfSPB::EachSPBTask); 
threeDimensionalVectorSPB = &threeDimensionalVectorSPBL;

static IfAllTrueSPB< 3,  false, 1> ifAllTrueSPBL; ifAllTrueSPBL.InitSPBObserver(StyleOfSPB::EachSPBTask); 
ifAllTrueSPB = &ifAllTrueSPBL;



//UserCode_Sectionbeforelinks
//	  sensor1filt1 = &sensor1L.Filter1;
//	sensor1filt2 = &sensor1L.Filter2;
//UserCode_Sectionbeforelinks_end
static float ifRightOnSPBchBuffer1[1];
ifRightOnSPB->AddSignalFlowLinkToChannelWithCopy1(sensor1, ifRightOnSPBchBuffer1, 0);
static float ifRightOnSPBchBuffer2[1];
ifRightOnSPB->AddSignalFlowLinkToChannelWithCopy2(sensor1, ifRightOnSPBchBuffer2, 0);
static float averageSPBchBuffer1[10];
averageSPB->AddSignalFlowLinkToChannelWithCopy1(sensor1, averageSPBchBuffer1, 0);
static float pidSPBchBuffer1[1];
pidSPB->AddSignalFlowLinkToChannelWithCopy1(sensor1, pidSPBchBuffer1, 0);
static float threeDimensionalVectorSPBchBuffer1[1];
threeDimensionalVectorSPB->AddSignalFlowLinkToChannelWithCopy1(sensor1, threeDimensionalVectorSPBchBuffer1, 0);
static float threeDimensionalVectorSPBchBuffer2[1];
threeDimensionalVectorSPB->AddSignalFlowLinkToChannelWithCopy2(sensor1, threeDimensionalVectorSPBchBuffer2, 0);
static float threeDimensionalVectorSPBchBuffer3[1];
threeDimensionalVectorSPB->AddSignalFlowLinkToChannelWithCopy3(sensor1, threeDimensionalVectorSPBchBuffer3, 0);
static float ifAllTrueSPBchBuffer1[1];
ifAllTrueSPB->AddSignalFlowLinkToChannelWithCopy1(sensor1, ifAllTrueSPBchBuffer1, 0);
static float ifAllTrueSPBchBuffer2[1];
ifAllTrueSPB->AddSignalFlowLinkToChannelWithCopy2(sensor1, ifAllTrueSPBchBuffer2, 0);
static float ifAllTrueSPBchBuffer3[1];
ifAllTrueSPB->AddSignalFlowLinkToChannelWithCopy3(sensor1, ifAllTrueSPBchBuffer3, 0);



//UserCode_Sectionbeforeclock
//UserCode_Sectionbeforeclock_end
clock1->SetObservorToClock(sensor1, AEClock_PrescalerEnum::PRESCALER1);


//AEITEST_END_TestsAfterTimer_commonAOs(5000);
//UserCode_Sectionb
	
	pidSPB->UserInitialize(50, 25, 25, 1, 5, 3, 0, 1000, 0);
//	pidSPB->UserInitialize(50, 25, 25, 1, 5, 3, 0, 1000 );
	
//	sensor1filt1->PastDataCircularBuffer.MutexForThisCircularBuffer = xSemaphoreCreateMutex();
//	sensor1filt2->PastDataCircularBuffer.MutexForThisCircularBuffer = xSemaphoreCreateMutex();
	
//	for (size_t i = 0; i < AllCircularBuffsInd; i++)
//	{
//		
//		AllCircularBuffs[i]->SetMutex(xSemaphoreCreateMutex());
//	}
	
//UserCode_Sectionb_end

AEAO::ConfigureAndStart();
}


//UserCode_Sectionc
//extern  int AllCircularBuffsInd;
//extern AEICircularBuffer* AllCircularBuffs[10];
//UserCode_Sectionc_end


static void clock1_callback(TimerHandle_t xTimerHandle) {  
  //UserCode_Sectionclock1before
	
	sensor1_data[0]++;
//UserCode_Sectionclock1before_end 
  
 clock1->Tick(); 
  //UserCode_Sectionclock1after
//UserCode_Sectionclock1after_end 
}


#endif