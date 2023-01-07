#include "ButtonDrive.h"



uint16_t ButtonDrive::IndexOfButtonDrivers = 0;
ButtonDrive* ButtonDrive::ButtonInstances[5];
 


  void vTimerCallback(TimerHandle_t xTimer)
{
	uint16_t forWhichButton = (uint32_t)pvTimerGetTimerID(xTimer);

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	//this means that the interrup triggered for the buttonperipheral
	//check the voltage level. if there was a change since the last update, send a ButtonChangedEvt, and change the enumstate

	//first get current pin state
	ButtonStateEnum currentstate = UP; 
	currentstate = (ButtonStateEnum)ButtonDrive::ButtonInstances[forWhichButton]->GpioIUse->GPIO_ReadPin();
	currentstate = (ButtonStateEnum)(!((bool)currentstate));
 
	//if the state changed, send an event
	if (currentstate != ButtonDrive::ButtonInstances[forWhichButton]->ButtonState)
	{
		ButtonChanged* evt = PoolManager->GetEvtFromPoolFromISR<ButtonChanged>();
		evt->ForButton = forWhichButton;
		evt->isButtonWentDown = currentstate == DOWN;
		PublishSubscribeManager->PublishEvtFromISR(evt);
	}

	//update current button state
	ButtonDrive::ButtonInstances[forWhichButton]->ButtonState = currentstate;
	
	if (forWhichButton == 0)
	{  
		Debounced0 = true;
	} 
	else if (forWhichButton == 1)
	{  
		Debounced1 = true;
	} 
	else if (forWhichButton == 2)
	{  
		Debounced2 = true;
	} 
	else if (forWhichButton == 3)
	{ 
		Debounced3 = true;
	} 
	else if (forWhichButton == 4)
	{  
		Debounced4 = true;
	}
	else
	{
		//ButtonDrive does not currently support more than 5 instances
		configASSERT(false);
	}
}





 void ButtonUpdate0()
{

	if (Debounced0 == true)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		Debounced0 = false;
		//start the timer to wait for the debounce 
		xTimerStartFromISR(ButtonDrive::ButtonInstances[0]->xTimerForButton, &xHigherPriorityTaskWoken);
	}

}



 void ButtonUpdate1() {
	if (Debounced1 == true)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		Debounced1 = false;
		//start the timer to wait for the debounce 
		xTimerStartFromISR(ButtonDrive::ButtonInstances[1]->xTimerForButton, &xHigherPriorityTaskWoken);
	}
}



 void ButtonUpdate2() {
	if (Debounced2 == true)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		Debounced2 = false;
		//start the timer to wait for the debounce 
		xTimerStartFromISR(ButtonDrive::ButtonInstances[2]->xTimerForButton, &xHigherPriorityTaskWoken);
	}
}



 void ButtonUpdate3() {
	if (Debounced3 == true)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		Debounced3 = false;
		//start the timer to wait for the debounce 
		xTimerStartFromISR(ButtonDrive::ButtonInstances[3]->xTimerForButton, &xHigherPriorityTaskWoken);
	}
}


 void ButtonUpdate4() {
	if (Debounced4 == true)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE; 
		Debounced4 = false;
		//start the timer to wait for the debounce 
		xTimerStartFromISR(ButtonDrive::ButtonInstances[4]->xTimerForButton, &xHigherPriorityTaskWoken);
	}
}