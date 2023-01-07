//generated file: C:/AERTOSProjects/commonHalAOs\include\DataToPC1_SPB.h
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
//UserCode_Sectionheader_end

template<bool isSubscribable, uint32_t CHANNELCOUNTBUFFER1, TEMPLATESPB_Filters>
	class DataToPC1_SPB :
		public AESPBObservorOutputType <1, 1, isSubscribable,
TEMPLATESPB_FilterParams,
CHANNELCOUNTBUFFER1, false>
	{
	public:
		DataToPC1_SPB();
		
		//UserCode_Sectionpublic
//UserCode_Sectionpublic_end


	protected: UploadDataToPcU* uploadDataUToUse; 
public: UploadDataToPcU*  GetuploadDataUToUse()   const {return uploadDataUToUse; }


public: void UserInitialize(UploadDataToPcU* _uploadDataUToUse )
	{
		uploadDataUToUse =  _uploadDataUToUse;

		
		//UserCode_SectionuserInited
//UserCode_SectionuserInited_end
		
		userInitialized = true;
	}
private: bool userInitialized = false;
protected: void CheckIfConfiguredProperly() const override  
	{
		//DataToPC1_SPB::CheckIfConfiguredProperly();
		if (userInitialized == false)
		{
			// you did not initialize one of your AEobjects
			AEAssertRuntime(userInitialized == true, "user did not call the UserInitailize function for  DataToPC1_SPB"); 
		} 
		 
	}
	
	private:
	//UserCode_Sectionprivate
		float _AllDataToSend[CHANNELCOUNTBUFFER1   ];
//UserCode_Sectionprivate_end

		void RefreshOVERRIDE(float OutputSignal[1]) override;

	};


//UserCode_Sectionfunc
//UserCode_Sectionfunc_end


template<bool isSubscribable, uint32_t CHANNELCOUNTBUFFER1, TEMPLATESPB_FiltersFunctionParams>
	inline DataToPC1_SPB< isSubscribable,  CHANNELCOUNTBUFFER1, TEMPLATESPB_FilterParams>::DataToPC1_SPB()
	{
		//UserCode_Sectionctor
//UserCode_Sectionctor_end
	}

template<bool isSubscribable, uint32_t CHANNELCOUNTBUFFER1, TEMPLATESPB_FiltersFunctionParams>
	inline void DataToPC1_SPB< isSubscribable,  CHANNELCOUNTBUFFER1, TEMPLATESPB_FilterParams>::RefreshOVERRIDE(float OutputSignal[1])
	{

		float* ch1 = this->InputChannels[0]->ChannelSignalBufferSingle; 

 
		//UserCode_Sectionrefresh
		memcpy(_AllDataToSend, 
			this->InputChannels[0]->ChannelSignalBufferSingle, CHANNELCOUNTBUFFER1  * sizeof(float)	);
		
		uploadDataUToUse->UploadDataToPC_WaitHereForFinish(this->GetAO_ID(), (char*)_AllDataToSend, CHANNELCOUNTBUFFER1);
		
//UserCode_Sectionrefresh_end
	}

