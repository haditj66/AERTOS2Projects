//generated file: C:/AERTOSProjects/commonHalAOs\include\PWMDriverU.h
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.

//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################


#pragma once

#include "AEUtilityAsService.h" 

#include "AEPublishSubscribeManager.h" 

#include "ActionRequestObjectArgTDU.h"
 
#include "AE_TDUAsService.h" 

#include "PWMDriverU_ServiceGen.h"


#include "GPIOsNeededForMotor.h"


//UserCode_Sectionheader
#include "AEPWM.h"
//UserCode_Sectionheader_end

class PWMDriverU :   
	 public AEService< 10 , AENullActionRequest, AENullActionRequest, AENullActionRequest, ActionRequestObjectArgTDU1<AENull , AENull, 10, PWMDriverU>, AENullActionRequest, AENullActionRequest >
{
public: 

	//UserCode_Sectionpublic
//UserCode_Sectionpublic_end
	 
	PWMDriverU ()
	{ 
		 //ActionReq1.ServiceName = "Transmit";
		
		
		ActionReq4.ServiceName = "StartPWMFromSPBLinked";
		
		 
		 
		PWMDriverU_CTOR
		
		//UserCode_Sectionctor
//UserCode_Sectionctor_end
		 	
	}
	PWMDriverU_Service
	
	
	protected: AEPWM* pwmThisUses; 
public: AEPWM*  GetpwmThisUses()   const {return pwmThisUses; }


public: void UserInitialize(AEPWM* _pwmThisUses )
	{
		pwmThisUses =  _pwmThisUses;

		
		//UserCode_SectionuserInited
//UserCode_SectionuserInited_end
		
		userInitialized = true;
	}
private: bool userInitialized = false;
protected: void CheckIfConfiguredProperly() const override  
	{
		//PWMDriverU::CheckIfConfiguredProperly();
		if (userInitialized == false)
		{
			// you did not initialize one of your AEobjects
			AEAssertRuntime(userInitialized == true, "user did not call the UserInitailize function for  PWMDriverU"); 
		} 
		 
	}
	
protected: 
	
	//UserCode_Sectionprot
//UserCode_Sectionprot_end
	
	
	//example for waiting on an event
	//actReq->WaitForEvent<SomeOther_Sig>(
	//				[](void* s, AEEventDiscriminator_t* evt)->void {
	//					//SomeOther_Sig* sssc = (SomeOther_Sig*)evt->evt;
	//					AEPrint("Event SomeOther_Sig recieved"); 
	//					return;
	//				}
	//				, 500);
	
	//dont forget to return the service value when finished
	//actReq->SetReturnArg(1); 
	
	//return true in the update function for tdus when the service is done.
	
	//=====================================
	//Normal services
	//=====================================
	  
	  
	  
	
	
	//=====================================
	//TDU services
	//=====================================
	void _StartPWMFromSPBLinked(AENull placeholder) 
   {

         //UserCode_SectionStartPWMFromSPBLinked
	  
	   AEAssertRuntime(this->spbIFlowTo != nullptr, "This service needes the utility to be set to a SPB's clock")
		   
		   pwmThisUses->StartPWM();
	   
	   
//UserCode_SectionStartPWMFromSPBLinked_end 
   }

void _StartPWMFromSPBLinkedCancelCleanup() 
   {

         //UserCode_SectionStartPWMFromSPBLinkedcancel
	   pwmThisUses->StopPWM();
//UserCode_SectionStartPWMFromSPBLinkedcancel_end 
   }

    bool _StartPWMFromSPBLinkedUpdate(ActionRequestObjectArgTDU1<AENull , AENull, 10, PWMDriverU>* request, AENull placeholder) 
   {

         //UserCode_SectionStartPWMFromSPBLinkedu
	   
	   pwmThisUses->ChangeDutyCycle(this->LinkedSPBData[0]);
	   
	   return false;
//UserCode_SectionStartPWMFromSPBLinkedu_end 
    return true; 
    }
  
	  
	  
	 
	  

};




//UserCode_Sectionfunc
//UserCode_Sectionfunc_end