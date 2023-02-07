#pragma once

#include "cstdint"
#include "AEUART.h"
#include <string>
#include <cstring>
#include <iostream>

#include "AEPublishSubscribeManager.h"
#include "AEAO.h"

#define RYLR896_CommandCopy(command, size) int cmd_size = size+2; memcpy(cmd,command ,size); RYLR896_Delimiters // cmd[size+2] = command

#define RYLR896_Delimiters \
cmd[cmd_size - 2] =  '\r'; cmd[cmd_size - 1] =  '\n';
//#define RYLR896_memcpy  memcpy(bufferForSendingShortCommands, cmd, cmd_size);


#define RYLR896_AddressCommand_SET "AT+ADDRESS=" //RYLR896_CommandCopy("AT+ADDRESS=", 11) //int cmd_size = 11+2; char cmd[11+2] = "AT+ADDRESS="; RYLR896_Delimiters RYLR896_memcpy
#define RYLR896_AddressCommand_GET "AT+ADDRESS?" //RYLR896_CommandCopy("AT+ADDRESS?", 11) //int cmd_size = 11+2; char cmd[11+2] = "AT+ADDRESS?";  RYLR896_Delimiters RYLR896_memcpy

#define RYLR896_Available_GET RYLR896_CommandCopy("AT", 2)

#define RYLR896_RFFrequency_SET RYLR896_CommandCopy("AT+BAND=", 8+9)
#define RYLR896_RFFrequency_GET RYLR896_CommandCopy("AT+BAND?", 8)

#define RYLR896_Parameter_SET RYLR896_CommandCopy("AT+PARAMETER=", 13)
#define RYLR896_Parameter_GET RYLR896_CommandCopy("AT+PARAMETER?", 13)

#define RYLR896_NETWORKID_SET RYLR896_CommandCopy("AT+NETWORKID=", 13)
#define RYLR896_NETWORKID_GET RYLR896_CommandCopy("AT+NETWORKID?", 13)

#define RYLR896_Send_SET RYLR896_CommandCopy("AT+SEND=", 8)
#define RYLR896_Send_GET RYLR896_CommandCopy("AT+SEND?", 8)

#define RYLR896_BufferSize 150


#define SET_END_DELIMITER 		\
int end = 0x0D;\
ind += sizeof(end); \
memcpy(&bufferForSendingShortCommands[ind - 1], &end, ind);\
end = 0x0A;\
ind += sizeof(end); \
memcpy(&bufferForSendingShortCommands[ind - 1], &end, ind);\


enum RYLR896_Bandwidth
{
	_7p8KHz =  0,
	_10p4KHz = 1,
	_15p6KHz = 2,
	_20p8KHz = 3,
	_31p25KHz =4,
	_41p7KHz = 5,
	_62p5KHz = 6,
	_127KHz =  7,
	_250KHz =  8,
	_500KHz =  9
	
};
enum RYLR896_SpreadFactor
{
	_7 = 7,
	_8 = 8,
	_9 = 9,
	_10 = 10,
	_11 = 11,
	_12 = 12,
	
};

class RYLR896Driver
{
public:
	
	
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	//LIMITATIONS!!!!: this lora module can technically be run as a transiever, HOWEVER this is very limited. If the module is busy sending data (which can easily take a full 2 seconds.) then it will miss any incoming messages.
	//BEST TO EITHER DESIGNATE IT AS EITHER A RECIEVER OR TRANSMITTER. OR AS A TRANSIEVER BUT WITH VERY MINIMAL TRANSMISSION OF DATA
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	///Address: address of your loramodule
	//bandwidth: bandwidth of data transmission. faster decreases range though. a value of _500KHz may not work.
	//SpreadFactor: SpreadFactor of data transmission. lower value is faster transmission but decreases range. a value of 7 may not work.
	RYLR896Driver(AEUART* uarperipheralToUse, int32_t Address, RYLR896_Bandwidth bandwidth = RYLR896_Bandwidth::_250KHz, RYLR896_SpreadFactor SpreadFactor = RYLR896_SpreadFactor::_8, int32_t RF_frequency = 868500000)
	{
		
		//put some delay 
		HAL_Delay(300);
		
		UarperipheralToUse = uarperipheralToUse; 
		AEAssertRuntime(UarperipheralToUse->GetMaxReceivedMsgSize() > 25, "the uart you are using for the RYLR896Driver needs to have at least a max rx size of 15");
		
		//callback for rx
		UARTPERIPHERAL_inst2->SetRxCpltCallback([](char* msgReceived, uint32_t sizeOfReceivedMsg) -> void { 
			//if the size is greather than 16, then the message could be a message from another lora module.
			//publish an OnLoraMsgReceived event
			if (sizeOfReceivedMsg > 16)
			{ 
				string rx = AE_convertToString(msgReceived, sizeOfReceivedMsg);
				//check if it is indeed a +RCV
				if (rx.find("RCV", 0) == true)
				{
					
					//populate an event for LoraMsgReceived
					LoraMsgReceived* evt = PoolManager->GetEvtFromPoolFromISR<LoraMsgReceived>();
					  
					
					//--------------example +RCV=2,8,kkkkaaaa,-37,43 
					
					//get number of digits of the lora address
					int ind = 0;
					int loraaddressDigits = 0;
					while (msgReceived[loraaddressDigits + 5] != ',') //5 for +RCV=
					{ 
						loraaddressDigits++;
					}
					ind += loraaddressDigits + 5; //+RCV=2
					
					int payloadsizeDigits = 0;
					while (msgReceived[payloadsizeDigits + 1 + ind] != ',')  
					{ 
						payloadsizeDigits++;
					}
					ind += payloadsizeDigits + 1; //+RCV=2,8
					
					evt->sendingLoraAddress = atoi(&msgReceived[5]);
					evt->payloadsize = atoi(&msgReceived[ind - payloadsizeDigits]);
					
					ind += 1; //+RCV=2,8,
					 
					memcpy(evt->payload, &msgReceived[ind], evt->payloadsize);
					
					//publish the populated event
					if (AEAO::GetAERTOSStarted() == true)
					{
						PublishSubscribeManager->PublishEvtFromISR(evt);

					}
					
					
					
					 
				} 
				

				
			}
			else
			{
				if (AEAO::GetAERTOSStarted() == true)
				{
					//otherwise this must be a response to a command, so just publish a response recieved signal
					PublishSubscribeManager->PublishEvtFromISR(&LoraCommandResponded_Instance); 
				}
				
			}
			
			
			
			
		}); 
		
		UarperipheralToUse->RecieveOnDelimiter('\n');
		SetAddress(Address);
		string rx = UarperipheralToUse->ReceiveMsgBlocking_String(); 
		bool ok = rx.find("OK", 0);
		AEAssertRuntime(ok == true, "RYLR896 seems to not be responding to changing it's address");
		
		//HAL_Delay(300); //DONT USE DELAY AS FREERTOS MESS WITh THe CLOCK!!
		SetRFFrequency(RF_frequency);
		rx = UarperipheralToUse->ReceiveMsgBlocking_String(); 
		ok = rx.find("OK", 0);
		AEAssertRuntime(ok == true, "RYLR896 seems to not be responding to changing it's frequency");
		 
		 
		SetNetworkID();
		rx = UarperipheralToUse->ReceiveMsgBlocking_String(); 
		ok = rx.find("OK", 0);
		AEAssertRuntime(ok == true, "RYLR896 seems to not be responding to changing it's networkid");
		 
		
		 
		SetParameters(bandwidth, SpreadFactor);
		rx = UarperipheralToUse->ReceiveMsgBlocking_String(); 
		ok = rx.find("OK", 0);
		AEAssertRuntime(ok == true, "RYLR896 seems to not be responding to changing it's networkid");
		
		//		UarperipheralToUse->SetRxCpltCallback([](char* msgReceived, uint32_t sizeOfReceivedMsg) -> void { 
		//			int dutycycle = (int)*msgReceived; // - '0'; 
		//		});
	}
	
	
	
	int16_t GetAddress_blocking()
	{
		//		int ind = 0; 
		//		ind += sizeof(RYLR896_AddressCommand_GET);
		//		memcpy(bufferForSendingShortCommands, RYLR896_AddressCommand_GET, ind); 
		//		SET_END_DELIMITER
		//		UarperipheralToUse->TansmitMsg(bufferForSendingShortCommands, ind);
		
		//		string sendbuffer = RYLR896_AddressCommand_GET; 
		//		string cmd = sendbuffer +   "\r\n";
		
		//		RYLR896_AddressCommand_GET
		
		string sendbuffer = "AT+ADDRESS?";
		string cmd2 = sendbuffer;
		cmd2 = cmd2 +  '\r' + '\n';
		memcpy(cmd, cmd2.c_str(), cmd2.size());
		
		//char ret2[10];
		UarperipheralToUse->TansmitMsg(cmd, cmd2.size()); 
		//HAL_UART_Receive(UarperipheralToUse->_uartHandle, (uint8_t*) ret2, 10, HAL_MAX_DELAY);
		string ret = UarperipheralToUse->ReceiveMsgBlocking_String();
		
		//the address is a int_16_t
		int16_t addre = 0;
		//memcpy(&addre, ret, 2);
		
//		string addrstr = AE_convertToString(ret, 11);
		if (ret.size() >= 9)
		{
			ret.replace(0, 9, "");
		
			addre = std::stoi(ret);
		
			return addre;
		}		 
		
		return 99999;
	}
	
	
	bool SetAddress_blocking(int16_t addressOfThisLoraModule)
	{
		SetAddress(addressOfThisLoraModule);
		string rx = UarperipheralToUse->ReceiveMsgBlocking_String(); 
		return rx.find("OK", 0); 
	}
	
	void SetAddress(int16_t addressOfThisLoraModule)
	{
 
		int ind = 0;
		
		string sendbuffer = "AT+ADDRESS=";
		string cmd2 = sendbuffer + std::to_string(addressOfThisLoraModule);
		cmd2 = cmd2 +  '\r' + '\n';
		memcpy(cmd, cmd2.c_str(), cmd2.size());
		//RYLR896_AddressCommand_SET
//		int cmd_size = 4;
//		char cmd[4] = "AT"; //{ 'A', 'T', '\r', '\n' }; // "AT" +  '\r' +'\n';
//		cmd[cmd_size - 2] =  '\r';
//		cmd[cmd_size - 1] =  '\n';
		
		
		
//		ind += sizeof(RYLR896_AddressCommand_SET);
//		memcpy(bufferForSendingShortCommands, RYLR896_AddressCommand_SET, ind);
//		ind += sizeof(addressOfThisLoraModule);
//		memcpy(&bufferForSendingShortCommands[ind - 1], &addressOfThisLoraModule, ind);
//		
//		
//		SET_END_DELIMITER 
//		UarperipheralToUse->TansmitMsg(bufferForSendingShortCommands, ind);
//		UarperipheralToUse->TansmitMsg(cmd.c_str(), cmd.size());
		UarperipheralToUse->TansmitMsg(cmd, cmd2.size());
		//		UarperipheralToUse->TansmitMsg((char*)0x41540d0a, 4);
		
				//memset(bufferForSendingShortCommands, 0,RYLR896_BufferSize);
	}
	
	
	bool SetRFFrequency_blocking(int32_t addressOfThisLoraModule = 868500000)
	{
		SetRFFrequency(addressOfThisLoraModule);
		string rx = UarperipheralToUse->ReceiveMsgBlocking_String(); 
		return rx.find("OK", 0); 
	}
	
	void SetRFFrequency(int32_t addressOfThisLoraModule = 868500000)
	{
		
		RYLR896_RFFrequency_SET
		//put frequency value into the cmd at the 11 position from last. frequency is always 9 digits long
		//first convert to char
		string addressOfThisLoraModuleSTR = std::to_string(addressOfThisLoraModule);	
		const char* addressOfThisLoraModulechar = addressOfThisLoraModuleSTR.c_str();
		
		memcpy(&cmd[cmd_size - 11], addressOfThisLoraModulechar, 9);
		
			
		UarperipheralToUse->TansmitMsg(cmd, cmd_size);
	}
	
	
	bool Reset_blocking()
	{
		Reset();
		string rx = UarperipheralToUse->ReceiveMsgBlocking_String();  
		return true;
	}
	
	void Reset()
	{ 
		string sendbuffer = "AT+RESET";
		string cmd2 = sendbuffer;
		cmd2 = cmd2 +  '\r' + '\n';
		memcpy(cmd, cmd2.c_str(), cmd2.size());
		
			
		UarperipheralToUse->TansmitMsg(cmd, cmd2.size());
	}
	
	
	bool isAvailable_blocking()
	{
		isAvailable();
		string rx = UarperipheralToUse->ReceiveMsgBlocking_String();  
		return rx.find("OK", 0); 
	}
	
	void isAvailable()
	{ 
		string sendbuffer = "AT";
		string cmd2 = sendbuffer;
		cmd2 = cmd2 +  '\r' + '\n';
		memcpy(cmd, cmd2.c_str(), cmd2.size());
		
			
		UarperipheralToUse->TansmitMsg(cmd, cmd2.size());
	}
	
	bool SetParameters_blocking(RYLR896_Bandwidth bandwidth = RYLR896_Bandwidth::_250KHz, RYLR896_SpreadFactor SpreadFactor = RYLR896_SpreadFactor::_8)
	{
		SetParameters(  bandwidth  , SpreadFactor );
		string rx = UarperipheralToUse->ReceiveMsgBlocking_String();  
		return rx.find("OK", 0); 
	}
	void SetParameters(RYLR896_Bandwidth bandwidth = RYLR896_Bandwidth::_250KHz, RYLR896_SpreadFactor SpreadFactor = RYLR896_SpreadFactor::_8)
	{ 
		string sendbuffer = "AT+PARAMETER=8,8,1,4";
		string bandwidthSTR = std::to_string(bandwidth);
		string SpreadFactorSTR = std::to_string(SpreadFactor);
		string codeRating = "1";
		string programpreamble = "4";
		string cmd2 = sendbuffer + bandwidthSTR + "," + SpreadFactorSTR + "," + codeRating + "," + programpreamble + ",";
		cmd2 = cmd2 +  '\r' + '\n';
		memcpy(cmd, cmd2.c_str(), cmd2.size());
		
			
		UarperipheralToUse->TansmitMsg(cmd, cmd2.size());
	}
	
	
	bool SetNetworkID_blocking()
	{
		SetNetworkID();
		string rx = UarperipheralToUse->ReceiveMsgBlocking_String();  
		return rx.find("OK", 0); 
	}
	void SetNetworkID()
	{ 
		string sendbuffer = "AT+NETWORKID=0";
		string cmd2 = sendbuffer;
		cmd2 = cmd2 +  '\r' + '\n';
		memcpy(cmd, cmd2.c_str(), cmd2.size());
		
			
		UarperipheralToUse->TansmitMsg(cmd, cmd2.size());
	}
	
	bool SendData_blocking(int16_t addressOfOtherLoraModule, float* dataToSend, int8_t numOfFloats)
	{
		return SendData_blocking(addressOfOtherLoraModule, (char*) dataToSend, numOfFloats * 4);
	}
	
	
	bool SendData_blocking(int16_t addressOfOtherLoraModule, char* dataToSend, int8_t sizeOfData)
	{
		SendData(addressOfOtherLoraModule, dataToSend, sizeOfData);
		string rx = UarperipheralToUse->ReceiveMsgBlocking_String();  
		return rx.find("OK", 0); 
	}
	
	
	///sizeOfData Maximum 240bytes
	void SendData(int16_t addressOfOtherLoraModule, float* dataToSend, int8_t numOfFloats)
	{
		SendData(addressOfOtherLoraModule, (char*) dataToSend, numOfFloats * 4);
	}
	
	
	///sizeOfData Maximum 240bytes
	void SendData(int16_t addressOfOtherLoraModule, char* dataToSend, int8_t sizeOfData)
	{
		//		if (true)
		//		{ 
		AEAssertRuntime(sizeOfData < 240, "you attempted to send more than 240 bytes in lora. Max is 240 byte payload.");
		
//		string sendbuffer = "AT+SEND="; //addressOfOtherLoraModule, sizeOfData, dataToSend
		string sizeOfDatastr = std::to_string(sizeOfData);
		string addressOfOtherLoraModulestr = std::to_string(addressOfOtherLoraModule);
//		int TotalsizeOfPacket = sendbuffer.size() + addressOfOtherLoraModulestr.size() + sizeOfDatastr.size();
//			
//		string cmd2  = sendbuffer  + addressOfOtherLoraModulestr + "," + sizeOfDatastr + ","; //+ AE_convertToString(dataToSend, sizeOfData);
//		
		int ind = 0;
		memcpy(cmd, "AT+SEND=", 8);
		ind += 8;
		memcpy(&cmd[ind], addressOfOtherLoraModulestr.c_str(), addressOfOtherLoraModulestr.size());
		ind += addressOfOtherLoraModulestr.size();
		memcpy(&cmd[ind], ",", 1);
		ind += 1;
		memcpy(&cmd[ind], sizeOfDatastr.c_str(), sizeOfDatastr.size()); 
		ind += sizeOfDatastr.size();
		memcpy(&cmd[ind], ",", 1);
		ind += 1;
		
//		memcpy(&cmd[ind], cmd2.c_str(), cmd2.size());
//		ind += cmd2.size(); 
		memcpy(&cmd[ind], dataToSend, sizeOfData);
		 
		ind += sizeOfData; 
		//		string cmd32 = ""+  '\r' + '\n';
		//		memcpy(&cmd[ind], cmd32.c_str(), cmd32.size());
		memcpy(&cmd[ind], "\r", 1);
		memcpy(&cmd[ind+1], "\n", 1);
		//		cmd[ind - 1] = (char)"\r";//'\r';
		//		cmd[ind] = (char)"\n";//'\n';
		//		cmd2 = cmd2 +  '\r' + '\n';
		//		memcpy(cmd, cmd2.c_str(), cmd2.size());
		
			
		UarperipheralToUse->TansmitMsg(cmd, ind+2);
			
			
		//			return ;
		//		}
		//		string sendbuffers = "AT+SEND=0,9,svasvasv\r\n";
		////		  sendbuffers = sendbuffers + '\r' + '\n';
		//		memcpy(cmd, sendbuffers.c_str(), sendbuffers.size());
		//		UarperipheralToUse->TansmitMsg(cmd, sendbuffers.size());
	}

	AEUART* GetUarperipheralToUse() const {return UarperipheralToUse;}
	
private:
	
	//char bufferForSendingShortCommands[RYLR896_BufferSize];
	char cmd[RYLR896_BufferSize];
	
	AEUART* UarperipheralToUse;
	
};
 