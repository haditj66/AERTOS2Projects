//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################


#define MotorDriverPWMU_RampUpToThisSpeed_CTOR ActionReq4.SetServiceFunc([](MotorDriverPWMU* p, float speedToRampUpTo){p->_RampUpToThisSpeed( speedToRampUpTo); });ActionReq4.SetUpdateFunc([](MotorDriverPWMU* p, float speedToRampUpTo) {return p->_RampUpToThisSpeedUpdate(&p->ActionReq4,  speedToRampUpTo); });ActionReq4.SetCancelCleanUpFunc([](MotorDriverPWMU* p){p->_RampUpToThisSpeedCancelCleanup(); });


//RampUpToThisSpeed----------------------------------------------

	  
	  
	#define MotorDriverPWMU_RampUpToThisSpeed_Service \
	inline void RampUpToThisSpeed(int idOfAO, float speedToRampUpTo)\
	{\
		this->RunRequest4(idOfAO,  speedToRampUpTo); \
	}\
	\
	inline Token* RampUpToThisSpeed_WithWait(int idOfAO, float speedToRampUpTo)\
	{\
		return this->RunRequestWithWait4(idOfAO,  speedToRampUpTo); \
	}\
	\
	inline Action4_RETURNTYPE_t RampUpToThisSpeed_WaitForRequestToFinish(Token* token)\
	{\
		return this->WaitForRequestToFinish4(token  ); \
	}\
	\
	inline void RampUpToThisSpeed_DoneWithRequest(Token* tokenOfRequest)\
	{\
		return this->DoneWithRequest4(tokenOfRequest); \
	}\
	inline Action4_RETURNTYPE_t RampUpToThisSpeed_WaitHereForFinish(int idOfAO, float speedToRampUpTo)\
	{\
		auto token = this->RunRequestWithWait4(idOfAO,  speedToRampUpTo);\
		Action4_RETURNTYPE_t ret = this->WaitForRequestToFinish4(token);\
		this->DoneWithRequest4(token);\
		return ret;\
	}
	
	#define MotorDriverPWMU_RampUpToThisSpeed void _RampUpToThisSpeed(int idOfAO, float speedToRampUpTo)
	#define MotorDriverPWMU_RampUpToThisSpeed_Update bool _RampUpToThisSpeedUpdate(ActionRequestObjectArgTDU1* actReq, float speedToRampUpTo)   
//Alldefines ------------------
#define MotorDriverPWMU_CTOR \
MotorDriverPWMU_RampUpToThisSpeed_CTOR 
#define MotorDriverPWMU_Service \
MotorDriverPWMU_RampUpToThisSpeed_Service 
