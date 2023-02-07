//generated file: C:/AERTOSProjects/loraTest\defaultTest.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.

//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################


 
#if INTEGRATION_TESTS_FOR_loraTest__defaultTest
 
#include "IntegTestPipeline.h"


#include "AECore.h"
#include "AE_Init.h" 
#include "AEClock.h" 
#include "AEObjects.h" 

DECLARE_ALL_AO_PTR

static void clock1_callback(TimerHandle_t xTimerHandle);
#include "LoopObjectTestlora.h"
static LoopObjectTestlora* loopObjectTestlora;




//UserCode_Sectiona
#include "RYLR896Driver.h"
#include "stm32f4xx_hal_uart.h"

   RYLR896Driver* ryld_ptr;
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_defaultTest()
{

AE_Init();
 //UserCode_Sectionbeforemain
	
	//-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	//BECAUSE RYLR896DRIVER NEEDS TO DO A HAL_DELAY , you cant use AEITEST_END_TestsAfterTimer_loraTest in any project that uses this!!
	//-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* 
//	AEITEST_END_TestsAfterTimer_loraTest(7000);
//	AEITEST_EXPECT_TEST_TO_RUN_loraTest("DriverInitialized");
//	AEITEST_EXPECT_TEST_TO_RUN_loraTest("tdumsglora");
	 
	
	static RYLR896Driver ryld(UARTPERIPHERAL_inst2, 2, RYLR896_Bandwidth::_250KHz, RYLR896_SpreadFactor::_8, 915000000);
	ryld_ptr = &ryld;
	
	
	
	if (true)
	{
//		HAL_Delay(300);
		ryld.SetRFFrequency_blocking(915000000);
		//	HAL_Delay(300);
		int efe = ryld.GetAddress_blocking();
	
		ryld.SendData_blocking(1, "svasvasv", sizeof("svasvasv"));
	
		float dat[3] = { 4.65, 45, 345.5 };
		ryld.SendData_blocking(1, dat, 3);
		
		AEITEST_loraTest("DriverInitialized",  true, "lora non-tdu calls passed");
	}
	

//	while (true)
//	{
//		ryld.SendData_blocking(0, "Hello", sizeof("Hello"));
		//ryld.SendData_blocking(1, "kkkkaaaa", 8);
//		ryld.SendData_blocking(0, "HelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHello", sizeof("HelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHello"));
//	}
	
	
//	while (true)
//	{
//		//HAL_Delay(1000);
//		//ryld.SetAddress(45);
//	}
	
	
//	UARTPERIPHERAL_inst2->SetRxCpltCallback([](char* msgReceived, uint32_t sizeOfReceivedMsg) -> void { 
//		int dutycycle = (int)*msgReceived; // - '0'; 
//	});
//	
//	
//	RYLR896Driver ryld(UARTPERIPHERAL_inst2,1);
	
//	ryld.SetAddress(45);
//	
//	int add = ryld.GetAddress( );
//	
//		
//
//	
//	UARTPERIPHERAL_inst2->TansmitMsg("AT\n", sizeof("AT\n"));
//	UARTPERIPHERAL_inst2->TansmitMsg("AT+RESET\n", sizeof("AT+RESET\n"));
//UserCode_Sectionbeforemain_end



static AEClock<AEObservorSensorDUMMY, AEObservorInterpretorBaseDUMMY, 0, 0, 1, 0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0> clock1L(200, clock1_callback);
clock1 = &clock1L;

static LoopObjectTestlora loopObjectTestlora_l;
loopObjectTestlora = &loopObjectTestlora_l;
loopObjectTestlora->InitObject(1, AEPriorities::MediumPriority);

static RYLR896_U rYLR896_U_L; rYLR896_U_L.Init(AEPriorities::MediumPriority);
rYLR896_U = &rYLR896_U_L;




//UserCode_Sectionbeforelinks
//UserCode_Sectionbeforelinks_end



//UserCode_Sectionbeforeclock
//UserCode_Sectionbeforeclock_end
clock1->SetTDUToClock(rYLR896_U, AEClock_PrescalerEnum::PRESCALER1);


//AEITEST_END_TestsAfterTimer_loraTest(5000);
//UserCode_Sectionb
	
	rYLR896_U->UserInitialize(ryld_ptr);
//UserCode_Sectionb_end

AEAO::ConfigureAndStart();
}


//UserCode_Sectionc
//UserCode_Sectionc_end


static void clock1_callback(TimerHandle_t xTimerHandle) {  
  //UserCode_Sectionclock1before
//UserCode_Sectionclock1before_end 
  
 clock1->Tick(); 
  //UserCode_Sectionclock1after
//UserCode_Sectionclock1after_end 
}


#endif