//generated file: C:/AERTOSProjects/commonAOs\include\IfRightOnSPB.h
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

template<bool isSubscribable, TEMPLATESPB_Filters>
	class IfRightOnSPB :
		public AESPBObservorOutputType <1, 2, isSubscribable,
TEMPLATESPB_FilterParams,
1, false,
1, false>
	{
	public:
		IfRightOnSPB();
		
		//UserCode_Sectionpublic
//UserCode_Sectionpublic_end


	
	
	private:
	//UserCode_Sectionprivate
//UserCode_Sectionprivate_end

		void RefreshOVERRIDE(float OutputSignal[1]) override;

	};


//UserCode_Sectionfunc
//UserCode_Sectionfunc_end


template<bool isSubscribable, TEMPLATESPB_FiltersFunctionParams>
	inline IfRightOnSPB< isSubscribable, TEMPLATESPB_FilterParams>::IfRightOnSPB()
	{
		//UserCode_Sectionctor
//UserCode_Sectionctor_end
	}

template<bool isSubscribable, TEMPLATESPB_FiltersFunctionParams>
	inline void IfRightOnSPB< isSubscribable, TEMPLATESPB_FilterParams>::RefreshOVERRIDE(float OutputSignal[1])
	{

		float* ch1 = this->InputChannels[0]->ChannelSignalBufferSingle; 
float* ch2 = this->InputChannels[1]->ChannelSignalBufferSingle; 

 
		//UserCode_Sectionrefresh

		
		if (*ch2 >= .999)
		{
			OutputSignal[0] = *ch1;
		}
		else
		{
			OutputSignal[0] = 0;
		}
		
//UserCode_Sectionrefresh_end
	}
