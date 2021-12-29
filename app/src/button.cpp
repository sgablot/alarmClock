/*
 * alarmClock.cpp
 *
 * Created: 29/12/2021 01:06:50
 * Author : Sylvain
 */ 

#include "button.h"

#include <avr/sfr_defs.h>

/************************************************************************/
/*                             PUSH BUTTON                              */
/************************************************************************/

//Constructor for the button: register address, pin number and the delay to avoir the rebound
Button::Button(volatile uint8_t* ddAddr, volatile uint8_t* portAddr, volatile uint8_t* pinAddr, uint8_t pinNo, uint16_t debounceDelay)
{
	this->ddAddr = ddAddr;
	this->portAddr = portAddr;
	this->pinAddr = pinAddr;
	this->pinNo = pinNo;
	
	this->debounceDelay = debounceDelay;
}


//Initilize register for pullup input
void Button::init()
{
	*ddAddr &= ~(1 << pinNo);
	*portAddr |= (1 << pinNo);
}

//Read the state of the button after a debounce system
void Button::refresh()
{
	//TODO Add debounce system with timer
	
	//Read the state of button after invertion (pullup)
	stateButton = bit_is_clear(*pinAddr, pinNo);
}

//Getter for stateButton
uint8_t Button::getStateButton()
{
	return stateButton;
}



/************************************************************************/
/*                            TOGGLE BUTTON                             */
/************************************************************************/

//Check if button is pressed when it was not
void Toggle::refresh()
{
	//Get and stock the last state of button
	uint8_t lastValue = Button::getStateButton();
	
	//Get and stock the current state of button
	Button::refresh();
	uint8_t currentValue = Button::getStateButton();
	
	//If the button is pressed when it was not -> invert the value of toggleValue
	if(currentValue && lastValue != currentValue)
	{
		toggleValue = !toggleValue;
	}
}

//Getter for toggleValue
uint8_t Toggle::getToggleValue()
{
	return toggleValue;
}

