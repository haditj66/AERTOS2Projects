#pragma once

#include <cstdint>
//there are four states of an encoder that it can transition to. 
//states:
//1. ZeroZero
//2. ZeroOne
//3. OneOne
//4. OneZero
//these states can move from one to the other sequentially example from 2 to 3.  or 3 to 2.  but not 2 to 4
//if it moves in such a way where one is skipped, there must have been a miscount 

enum EncoderStateEnum : int8_t
{
	ZeroZero = 0,
	ZeroOne = 1,
	OneOne = 3,
	OneZero = 2
};