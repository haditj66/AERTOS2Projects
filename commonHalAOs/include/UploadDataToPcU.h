//generated file: C:/AERTOSProjects/commonHalAOs\include\UploadDataToPcU.h
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

#include "UploadDataToPcU_ServiceGen.h"




//UserCode_Sectionheader

#include "AEUART.h"

//for no. TODO: make it into a cgen option
#define MAXPACKETSIZE  2100

//UserCode_Sectionheader_end

class UploadDataToPcU :   
	 public AEService< 10 , AENullActionRequest, AENullActionRequest, AENullActionRequest, ActionRequestObjectArgTDU2<char* , uint16_t , bool, 10, UploadDataToPcU>, ActionRequestObjectArgTDU1<bool , bool, 10, UploadDataToPcU>, AENullActionRequest >
{
public: 

	//UserCode_Sectionpublic
//UserCode_Sectionpublic_end
	 
	UploadDataToPcU ()
	{ 
		 //ActionReq1.ServiceName = "Transmit";
		
		
		ActionReq4.ServiceName = "UploadDataToPC";
		ActionReq5.ServiceName = "CheckIfThereIsPCConnection";
		 
		 
		UploadDataToPcU_CTOR
		
		//UserCode_Sectionctor
			
			
		evtToWaitFor = TotalNumOfUploadsCreated == 0 ? ProjectEventSignals::UploadDataUartRx1 : ProjectEventSignals::UploadDataUartRx2;
		
		
		TotalNumOfUploadsCreated++;
		IdUploadsCreated = TotalNumOfUploadsCreated;
		 
		
//UserCode_Sectionctor_end
		 	
	}
	UploadDataToPcU_Service
	
	
	protected: AEUART* uartPeripheralToUse; 
public: AEUART*  GetuartPeripheralToUse()   const {return uartPeripheralToUse; }
public:  void SetuartPeripheralToUse(AEUART*  _uartPeripheralToUse){uartPeripheralToUse = _uartPeripheralToUse; }


public: void UserInitialize(AEUART* _uartPeripheralToUse )
	{
		uartPeripheralToUse =  _uartPeripheralToUse;

		
		//UserCode_SectionuserInited
		
		if (this->evtToWaitFor == ProjectEventSignals::UploadDataUartRx1)
		{
			uartPeripheralToUse->SetRxCpltCallback([](char* msgReceived, uint32_t sizeOfReceivedMsg) -> void {
				PublishSubscribeManager->PublishEvtFromISR(&UploadDataUartRx1_Instance);
			});
		}
		else
		{
			uartPeripheralToUse->SetRxCpltCallback([](char* msgReceived, uint32_t sizeOfReceivedMsg) -> void {
				PublishSubscribeManager->PublishEvtFromISR(&UploadDataUartRx2_Instance);
			});	
		}

		
//UserCode_SectionuserInited_end
		
		userInitialized = true;
	}
private: bool userInitialized = false;
protected: void CheckIfConfiguredProperly() const override  
	{
		//UploadDataToPcU::CheckIfConfiguredProperly();
		if (userInitialized == false)
		{
			// you did not initialize one of your AEobjects
			AEAssertRuntime(userInitialized == true, "user did not call the UserInitailize function for  UploadDataToPcU"); 
		} 
		 
	}
	
protected: 
	
	//UserCode_Sectionprot
	
	static uint8_t TotalNumOfUploadsCreated;
	uint8_t IdUploadsCreated;
	ProjectEventSignals evtToWaitFor;
	uint16_t AttemptsOfConnecting;
	
	
	bool firstUpdate;
	
	char* BufferDataToUpload;
	char PacketBuffer[MAXPACKETSIZE + 16]; //the 16 is because of the extra space needed for the starting__finished = 8+8;
	uint16_t SizeOfData;
	uint16_t Remainder;
	int32_t BytesWrittenSoFar;
	int16_t PacketSize;
	int16_t NumPacketsNeededToSend;
	 
	Token* tokenForWaitingForUartRequests;

	uint16_t PacketsWrittenSoFar;
	
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
	void _UploadDataToPC(char* DataToSend, uint16_t SizeOfData) 
   {

         //UserCode_SectionUploadDataToPC
	   
	   
	   this->BufferDataToUpload = DataToSend;
	   this->SizeOfData = SizeOfData;
	   bool isdivisible = false;
	   PacketsWrittenSoFar = 0;
	   Remainder = 0;


	   //if size of data is larger than the MAXPACKETSIZE, then I will need to send
	   //the data in more than one pack. if not, I can send it in one packet 
	   if (SizeOfData < MAXPACKETSIZE)
	   {
		   NumPacketsNeededToSend = 1;
		   PacketSize = SizeOfData;
		   isdivisible = true;
	   }
	   else
	   {

		   uint32_t remainder = SizeOfData % MAXPACKETSIZE; 
		   //get the largest packet size that is is divisible into the SizeOfData 

		   //I already know that sizeOfData is greater then MAXPACKETSIZE so I know remainder will be
		   //of the division remainder  
		   if (remainder == 0)
		   {
			   Remainder = 0;
			   NumPacketsNeededToSend = SizeOfData / MAXPACKETSIZE;
			   PacketSize = MAXPACKETSIZE;
			   isdivisible = true;
		   }
		   //if remainder is still less thean the number I am dividing by, I can 
		   //use this as the remainder
		   else
		   {
			   Remainder = remainder;
			   NumPacketsNeededToSend = 1 + floor(SizeOfData / MAXPACKETSIZE);
			   PacketSize = MAXPACKETSIZE;
			   isdivisible = true;
		   }

	   }

 

	   //assert that the SizeOfDatabeing sent is divisible by either 200,100,50,20,10, 8, or 4  and is greater or equal to 4
	   AEAssertRuntime((SizeOfData >= 4) && (isdivisible), "for UploadDataToPC assert failed that the SizeOfDatabeing sent needs to be divisible by either 200,100,50,20,10, 8, or 4  and is greater or equal to 4");


	   firstUpdate = true;
	   
	    
	   
//UserCode_SectionUploadDataToPC_end 
   }

void _UploadDataToPCCancelCleanup() 
   {

         //UserCode_SectionUploadDataToPCcancel
//UserCode_SectionUploadDataToPCcancel_end 
   }

    bool _UploadDataToPCUpdate(ActionRequestObjectArgTDU2<char* , uint16_t , bool, 10, UploadDataToPcU>* request, char* DataToSend, uint16_t SizeOfData) 
   {

         //UserCode_SectionUploadDataToPCu
	   
	    
	   if (firstUpdate == true)
	   { 
			uartPeripheralToUse->TansmitMsg("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", sizeof("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"));
			   //->RunRequestWithWait1<ActionRequestForUARTTransmit>(this->AOID_OfResource, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", sizeof("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"));
		 	   //you need to wait for the uart to be sure to finish as it could write over the buffer the uart is sending
				//since the buffer is the same everytime, if code reaches here, the data being sent will be written over as it is being sent. 
		   
		   firstUpdate = false;
		   return false; 
 
	   } 


	   if (Remainder > 0)
	   {
		   if (PacketsWrittenSoFar == NumPacketsNeededToSend - 1)
		   {
			   //set last write as the remainder
			   PacketSize = Remainder;
		   }
	   }
 
	

	   //clear the packetbuffer
	   memset(PacketBuffer, '0', MAXPACKETSIZE + 16);
	   memcpy(PacketBuffer, "starting", 8);
	   memcpy(PacketBuffer + 8, BufferDataToUpload + BytesWrittenSoFar, PacketSize);
	   memcpy(PacketBuffer + 8 + PacketSize, "finished", 8);

	   //writing to the pc using the uart
	   //static ::UartTransmitArgs_t arg; arg.msgToSend = PacketBuffer; arg.sizeOfMsg = PacketSize + 8 + 8;
	   uartPeripheralToUse->TansmitMsg(PacketBuffer, PacketSize + 8 + 8);
		   //uartDriver->RunRequestWithWait1<ActionRequestForUARTTransmit>(this->AOID_OfResource, PacketBuffer, PacketSize + 8 + 8);


	   BytesWrittenSoFar += PacketSize;
	   PacketsWrittenSoFar++;

        
        
	   /*
	   #ifdef Target_RealUART

	   	//i need to wait for the pc to tell me it is done with the data sent before I can proceed to send more 
	   	//this->WaitForEvent<ProjectEventSignals::Uart2RecieveEVT_Evt>(nullptr);
	   	bool eventFound = this->WaitForEventWithTimeOutAttempts<ProjectEventSignals::Uart2RecieveEVT_Evt>(nullptr, TimeOutTime, AttemptsToConntectAfterTimeout, [](void* p)->void {
	   		UploadDataToPC_AR* thisUploadToPC = static_cast<UploadDataToPC_AR*>(p);
	   		CallBackForEvtWaitTimeout(thisUploadToPC);
	   	});
	   	if (eventFound == false)
	   	{
	   		this->SetReturnArg(false);
	   		return true;
	   	}


	   	#endif // Target_RealUART
	   	*/
        
        
        
	   if (BytesWrittenSoFar >= SizeOfData)
	   {
//		   uartDriver->WaitForRequestToFinish1<ActionRequestForUARTTransmit>(tokenForWaitingForUartRequests);
//		   uartDriver->DoneWithRequest1<ActionRequestForUARTTransmit>(tokenForWaitingForUartRequests);


		   //static char* endindingmsg = "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq";
		   uartPeripheralToUse->TansmitMsg("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq", sizeof("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"));
//		   this->ClassForActionRequest->UuartDriver->RunRequest_TransmitMsg(this->ClassForActionRequest,
//			   "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq",
//			   sizeof("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"));
 

		   BytesWrittenSoFar = 0;
		   request->SetReturnArg(true);
		   return true;
	   }
	   return false; 
	   
//UserCode_SectionUploadDataToPCu_end 
    return true; 
    }
  
	void _CheckIfThereIsPCConnection(bool placeHolderArg) 
   {

         //UserCode_SectionCheckIfThereIsPCConnection
//UserCode_SectionCheckIfThereIsPCConnection_end 
   }

void _CheckIfThereIsPCConnectionCancelCleanup() 
   {

         //UserCode_SectionCheckIfThereIsPCConnectioncancel
	   AttemptsOfConnecting = 0;
//UserCode_SectionCheckIfThereIsPCConnectioncancel_end 
   }

    bool _CheckIfThereIsPCConnectionUpdate(ActionRequestObjectArgTDU1<bool , bool, 10, UploadDataToPcU>* request, bool placeHolderArg) 
   {

         //UserCode_SectionCheckIfThereIsPCConnectionu
	   
	   // read from the uart driver recieve buffer and do this 10 times. If I get the message, "Im here" then the PC is there.
	// I can publish a PC connected signal on the 10 try to let anyone know if the PC is ready. 

	   uartPeripheralToUse->TansmitMsg("PC are you there", sizeof("PC are you there"));

	   
	   request->SetReturnArg(false);
	//I need to wait for a uartRecievedEvt
	   request->WaitForEvent(this->evtToWaitFor, [](void* p, AEEventDiscriminator_t* evt)->void
	   {

		   auto thisAO = static_cast<UploadDataToPcU*>(p);  
		   
		   uint8_t cmpValue = strcmp(thisAO->uartPeripheralToUse->_ReadBuffer, "\n");
		   
		   if (cmpValue == 0)
		   {
			   thisAO->ActionReq5.SetReturnArg(true);
		   }
		   if (cmpValue != 0)
		   {
			   thisAO->ActionReq5.SetReturnArg(false);
			   
			   if (thisAO->AttemptsOfConnecting >= 10)
			   { 
				   thisAO->ActionReq5.SetReturnArg(false); 
			   }
		   }
		   
		   thisAO->AttemptsOfConnecting++;
		    
//		   
//		   Uart2RecieveEVT* evtUart = (Uart2RecieveEVT*)evt->evt;
//
//		   // cmpValue = 0 if they are exactly the same
//		   // cmpValue = -1 if str1 < str2
//		   // cmpValue = 1 if str1 > str2
//		   uint8_t cmpValue = strcmp(evtUart->readBuffer, "Im here");
//
//		   if (cmpValue == 0)
//		   {
//			   //if the same then you can publish the event that says the pc is connected.
//			   auto evt = PoolManager->GetEvtFromPool<PCConnecttionCheckEVT>();
//			   evt->isConnected = true;
//			   thisAO->PostEvtToRequestingAO(evt);
//			   thisAO->SetReturnArg(true);
//			   //return true;
//		   }
//
//		   //if by the 10 time the message has still not been recieved, then give up and say that there is a problem with the connection
//		   if (cmpValue != 0)
//		   {
//			   if (thisAO->AttemptsOfConnecting >= 10)
//			   {
//				   auto evt = PoolManager->GetEvtFromPool<PCConnecttionCheckEVT>();
//				   evt->isConnected = true;
//				   thisAO->PostEvtToRequestingAO(evt);
//				   thisAO->SetReturnArg(false);
//				   //return true;
//			   }
//
//		   }
//
//		   thisAO->AttemptsOfConnecting++;

	   }, 1500);
	    
	   return true;
	   
//UserCode_SectionCheckIfThereIsPCConnectionu_end 
    return true; 
    }
  
	  
	 
	  

};




//UserCode_Sectionfunc
//UserCode_Sectionfunc_end