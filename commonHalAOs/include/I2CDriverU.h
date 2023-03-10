//generated file: C:/Users/hadi/Documents/AERTOSProjects/commonHalAOs\include\I2CDriverU.h
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

#include "I2CDriverU_ServiceGen.h"


#include "GPIOsNeededForMotor.h"


//UserCode_Sectionheader
#include "AEI2C.h"
//UserCode_Sectionheader_end

class I2CDriverU :   
	 public AEService< 10 , AENullActionRequest, AENullActionRequest, AENullActionRequest, ActionRequestObjectArgTDU4<uint8_t , uint8_t , uint8_t , uint8_t* , bool, 10, I2CDriverU>, ActionRequestObjectArgTDU4<uint8_t , uint8_t , uint8_t , uint8_t* , bool, 10, I2CDriverU>, AENullActionRequest >
{
public: 

	//UserCode_Sectionpublic
//UserCode_Sectionpublic_end
	 
	I2CDriverU ()
	{ 
		 //ActionReq1.ServiceName = "Transmit";
		
		
		ActionReq4.ServiceName = "WriteBytes";
		ActionReq5.ServiceName = "ReadBytes";
		 
		 
		I2CDriverU_CTOR
		
		//UserCode_Sectionctor
			 
			TotalIdOfDriver++;
		
		IdOfDriver = TotalIdOfDriver;
		if (IdOfDriver == 1)
		{
			i2cThisUses->SetI2C_MasterTxCpltCallback([](AEI2C* i2cper) -> void { 
				PublishSubscribeManager->PublishEvtFromISR(&I2CTXCmplt1_Instance);  
			}); 
			i2cThisUses->SetI2C_MasterRxCpltCallback([](AEI2C* i2cper) -> void { 
				PublishSubscribeManager->PublishEvtFromISR(&I2CRXCmplt1_Instance);  
			}); 
		}
		else if (IdOfDriver == 2)
		{
			i2cThisUses->SetI2C_MasterTxCpltCallback([](AEI2C* i2cper) -> void { 
				PublishSubscribeManager->PublishEvtFromISR(&I2CTXCmplt2_Instance);  
			}); 
			i2cThisUses->SetI2C_MasterRxCpltCallback([](AEI2C* i2cper) -> void { 
				PublishSubscribeManager->PublishEvtFromISR(&I2CRXCmplt2_Instance);  
			}); 
		}
		
		AEAssertRuntime(IdOfDriver <= 2, "Currently only two drivers supported");

//UserCode_Sectionctor_end
		 	
	}
	I2CDriverU_Service
	
	
	protected: AEI2C* i2cThisUses; 
public: AEI2C*  Geti2cThisUses()   const {return i2cThisUses; }


public: void UserInitialize(AEI2C* _i2cThisUses )
	{
		i2cThisUses =  _i2cThisUses;

		
		//UserCode_SectionuserInited
//UserCode_SectionuserInited_end
		
		userInitialized = true;
	}
private: bool userInitialized = false;
protected: void CheckIfConfiguredProperly() const override  
	{
		//I2CDriverU::CheckIfConfiguredProperly();
		if (userInitialized == false)
		{
			// you did not initialize one of your AEobjects
			AEAssertRuntime(userInitialized == true, "user did not call the UserInitailize function for  I2CDriverU"); 
		} 
		 
	}
	
protected: 
	
	//UserCode_Sectionprot
	static int TotalIdOfDriver;
	int IdOfDriver;
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
	void _WriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* dataToWrite) 
   {

         //UserCode_SectionWriteBytes
//UserCode_SectionWriteBytes_end 
   }

void _WriteBytesCancelCleanup() 
   {

         //UserCode_SectionWriteBytescancel
//UserCode_SectionWriteBytescancel_end 
   }

    bool _WriteBytesUpdate(ActionRequestObjectArgTDU4<uint8_t , uint8_t , uint8_t , uint8_t* , bool, 10, I2CDriverU>* request, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* dataToWrite) 
   {

         //UserCode_SectionWriteBytesu
	   
	   
	   this->i2cThisUses->WriteBytes(devAddr, regAddr, length, dataToWrite);

	    
	   if (IdOfDriver == 1)
	   {
		   bool eventFound = request->WaitForEventWithTimeOutAttempts<ProjectEventSignals::I2CTXCmplt1>(nullptr, 1, 3,
			 [](void* p)->void {
			   //TODO: if this does not trigger than there must be a problem with the I2C. attempt to reboot it. 
		   });
	   }
	   else if (IdOfDriver == 2)
	   {
		   bool eventFound = request->WaitForEventWithTimeOutAttempts<ProjectEventSignals::I2CTXCmplt2>(nullptr, 1, 3,
			[](void* p)->void {
			   //TODO: if this does not trigger than there must be a problem with the I2C. attempt to reboot it. 
		   });
	   } 

	   return true;
 
//UserCode_SectionWriteBytesu_end 
    return true; 
    }
  
	void _ReadBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* pdataToWriteTo) 
   {

         //UserCode_SectionReadBytes
//UserCode_SectionReadBytes_end 
   }

void _ReadBytesCancelCleanup() 
   {

         //UserCode_SectionReadBytescancel
//UserCode_SectionReadBytescancel_end 
   }

    bool _ReadBytesUpdate(ActionRequestObjectArgTDU4<uint8_t , uint8_t , uint8_t , uint8_t* , bool, 10, I2CDriverU>* request, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* pdataToWriteTo) 
   {

         //UserCode_SectionReadBytesu
	   
	   this->i2cThisUses->ReadBytes(devAddr, length, pdataToWriteTo);

	   
	   if (IdOfDriver == 1)
	   {
		   bool eventFound = request->WaitForEventWithTimeOutAttempts<ProjectEventSignals::I2CRXCmplt1>(nullptr, 1, 3,
			[](void* p)->void {
			   //TODO: if this does not trigger than there must be a problem with the I2C. attempt to reboot it. 
		   });
	   }		
	   else if (IdOfDriver == 2)
	   {
		   bool eventFound = request->WaitForEventWithTimeOutAttempts<ProjectEventSignals::I2CRXCmplt2>(nullptr, 1, 3,
			[](void* p)->void {
			   //TODO: if this does not trigger than there must be a problem with the I2C. attempt to reboot it. 
		   });
		   
	   }
//UserCode_SectionReadBytesu_end 
    return true; 
    }
  
	  
	 
	  

};




//UserCode_Sectionfunc
//UserCode_Sectionfunc_end