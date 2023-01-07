#pragma once

#include <cstdint>

#include "FreeRTOS.h"
#include "AEGPIOInput.h"
 

#include "AEPublishSubscribeManager.h"

enum ButtonStateEnum
{
	DOWN,
	UP
};





 void ButtonUpdate0();
 void ButtonUpdate1();
 void ButtonUpdate2();
 void ButtonUpdate3();
 void ButtonUpdate4();
void vTimerCallback(TimerHandle_t xTimer);

static bool Debounced0 = true;
static bool Debounced1 = true;
static bool Debounced2 = true;
static bool Debounced3 = true;
static bool Debounced4 = true;

class ButtonDrive
{

	friend void ButtonUpdate0();
	friend void ButtonUpdate1();
	friend void ButtonUpdate2();
	friend void ButtonUpdate3();
	friend void ButtonUpdate4();

	friend void vTimerCallback(TimerHandle_t xTimer);

public:

	ButtonDrive()
	{}
	 
	AEGPIOInput* GpioIUse;
	void Init(AEGPIOInput* gpioInput) {
		
 
		GpioIUse = gpioInput;
		 
		ButtonState = (ButtonStateEnum)(!((bool)GpioIUse->GPIO_ReadPin()));
		
		if (IndexOfButtonDrivers == 0)
		{
			ButtonInstances[0] = this;
			portButton = gpioInput->buttongpio_Port;
			pinButton = gpioInput->buttongpio_Pin;
			gpioInput->AE_GPIO_extiCallback = ButtonUpdate0;
		}
		else if (IndexOfButtonDrivers == 1)
		{
			ButtonInstances[1] = this;
			portButton = gpioInput->buttongpio_Port;
			pinButton = gpioInput->buttongpio_Pin;
			gpioInput->AE_GPIO_extiCallback = ButtonUpdate1;
		}
		else if (IndexOfButtonDrivers == 2)
		{
			ButtonInstances[2] = this;
			portButton = gpioInput->buttongpio_Port;
			pinButton = gpioInput->buttongpio_Pin;
			gpioInput->AE_GPIO_extiCallback = ButtonUpdate2;
		}
		else if (IndexOfButtonDrivers == 3)
		{
			ButtonInstances[3] = this;
			portButton = gpioInput->buttongpio_Port;
			pinButton = gpioInput->buttongpio_Pin;
			gpioInput->AE_GPIO_extiCallback = ButtonUpdate3;
		}
		else if (IndexOfButtonDrivers > 4)
		{
			ButtonInstances[4] = this;
			portButton = gpioInput->buttongpio_Port;
			pinButton = gpioInput->buttongpio_Pin;
			gpioInput->AE_GPIO_extiCallback = ButtonUpdate4;
		}
		else
		{
			//ButtonDrive does not currently support more than 5 instances
			configASSERT(false);
		}


		xTimerForButton = xTimerCreate
		( /* Just a text name, not used by the RTOS
		  kernel. */
			"Timer",
			/* The timer period in ticks, must be
			greater than 0. */
			30,
			/* The timers will auto-reload themselves
			when they expire. */
			pdFALSE,
			//an id of the timer 
			(void *)IndexOfButtonDrivers,
			/* Each timer calls the same callback when
			it expires. */
			vTimerCallback);



		IndexOfButtonDrivers++;

	}

	TimerHandle_t xTimerForButton;

	Port_t portButton;
	Pin_t pinButton;

	ButtonStateEnum ButtonState;
 

private:

	static uint16_t IndexOfButtonDrivers;
	static ButtonDrive* ButtonInstances[5];

};



