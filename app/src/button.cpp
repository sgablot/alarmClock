/*
 * alarmClock.cpp
 *
 * Created: 29/12/2021 01:06:50
 * Author : Sylvain
 */ 

#include "button.h"

#include <avr/sfr_defs.h>
#include "timer.h"


/************************************************************************/
/*                             PUSH BUTTON                              */
/************************************************************************/

//Constructor for the button: register address and pin number
Button::Button(volatile uint8_t* ddAddr, volatile uint8_t* portAddr, volatile uint8_t* pinAddr, uint8_t pinNo)
{
	this->ddAddr = ddAddr;
	this->portAddr = portAddr;
	this->pinAddr = pinAddr;
	this->pinNo = pinNo;
}


//Initilize register for pullup input
void Button::init(void)
{
	*ddAddr &= ~(1 << pinNo);
	*portAddr |= (1 << pinNo);
}

//Read the state of the button after a debounce system
void Button::refresh(void)
{
	//Stock the old state of button
	lastState = stateButton;
	
	//Read the state of button after invertion (pullup)
	stateButton = bit_is_clear(*pinAddr, pinNo);
}

//Getter for stateButton
uint8_t Button::getStateButton(void)
{
	return stateButton;
}

//Return 1 when state of button go LOW to HIGH
uint8_t Button::isPressed(void)
{
	//1 When stateButton=1 and lastState=0
	return stateButton & ~lastState;
}

//Return 1 when state of button go HIGH to LOW
uint8_t Button::isReleased(void)
{
	//1 When stateButton=0 and lastState=1
	return ~stateButton & lastState;
}



/************************************************************************/
/*                            TOGGLE BUTTON                             */
/************************************************************************/

//Check if button is pressed when it was not
void Toggle::refresh(void)
{
	//Read the state of button	
	Button::refresh();
	
	//If the button is pressed when it was not -> invert the value of toggleValue
	if(stateButton & ~lastState)	//Same Button::isPressed()
	{
		toggleValue = !toggleValue;
	}
}

//Getter for toggleValue
uint8_t Toggle::getToggleValue(void)
{
	return toggleValue;
}



/************************************************************************/
/*                          BUTTON DECLARATION                          */
/************************************************************************/

Button button_plus = Button(BUTTON_PLUS_ADDR);
Button button_less = Button(BUTTON_LESS_ADDR);
Toggle button_state = Toggle(BUTTON_STATE_ADDR);
Button button_stop = Button(BUTTON_STOP_ADDR);
Button button_set = Button(BUTTON_SET_ADDR);



/************************************************************************/
/*                        BUTTON GLOBAL FUNCTION                        */
/************************************************************************/

//Function for initialize all buttons
void button_init(void)
{
	button_plus.init();
	button_less.init();
	button_state.init();
	button_stop.init();
	button_set.init();
}

//Function for refresh all buttons with debounce system
void buttons_refresh(void)
{
	//Read the debounce timer and refresh all button every 1ms
	if(getDebounceTimer() >= 1)
	{
		button_plus.refresh();
		button_less.refresh();
		button_state.refresh();
		button_stop.refresh();
		button_set.refresh();
		
		resetDebounceTimer();
	}
}
