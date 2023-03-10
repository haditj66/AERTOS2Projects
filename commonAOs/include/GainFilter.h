//generated file: C:/AERTOSProjects/commonAOs\include\GainFilter.h
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.

//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################

#pragma once 

#include <cstdint>
#include "AEFilter.h"


//UserCode_Sectionheader
//UserCode_Sectionheader_end

template<class _gain >
class GainFilter //: public Filter<GainFilter< _gain >, 1>
{
  template<class TFilterDerived, uint16_t PastDataBufferSize>
	friend class Filter;

public:

float G_gain; 


//UserCode_Sectionpubl
//UserCode_Sectionpubl_end

	GainFilter();

protected:

//UserCode_Sectionprot
//UserCode_Sectionprot_end
	
	void InitializeImpl(float samplingPeriodOfObservorInSeconds);

	const float*  PastDataCircularBuffer;
	float SamplingPeriodOfObservorInSeconds;
	uint16_t PastDataBufferSize;

private:
	float RunFilter(float newestInput);
	
	//UserCode_Sectionpriv
//UserCode_Sectionpriv_end
	

};

template<class _gain >
inline GainFilter< _gain >::GainFilter()
{
	_gain T_gain; 
 G_gain =  T_gain.GetValue(); 

	//UserCode_Sectionctor
//UserCode_Sectionctor_end
}
 
template<class _gain >
inline void GainFilter< _gain >::InitializeImpl(float samplingPeriodOfObservorInSeconds)
{
	//UserCode_Sectioninit
//UserCode_Sectioninit_end
}

template<class _gain >
inline float GainFilter< _gain >::RunFilter(float newestInput)
{
//PastDataCircularBuffer[0] is the newest input
//example: float der = (PastDataCircularBuffer[0] - PastDataCircularBuffer[1]) / this->SamplingPeriodOfObservorInSeconds;
//return the output of the filter
//return der;

//UserCode_Sectionimpl
	
	return G_gain * newestInput;
//UserCode_Sectionimpl_end
 
}


//UserCode_Sectionfunc
//UserCode_Sectionfunc_end