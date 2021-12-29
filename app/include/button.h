/*
 * button.h
 *
 * Created: 29/12/2021 01:07:07
 *  Author: Sylvain
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>

/************************************************************************/
/*                             PUSH BUTTON                              */
/************************************************************************/

//TODO Add when button is pressed and when is released function
class Button
{
public:
	//Constructor for the button: register address, pin number and the delay to avoid the rebound
	Button(volatile uint8_t* ddAddr, volatile uint8_t* portAddr, volatile uint8_t* pinAddr, uint8_t pinNo, uint16_t debounceDelay);
	
	//Initilize register for pullup input
	void init();
	//Read the state of the button after a debounce system
	void refresh();
	
	//Getter for stateButton
	uint8_t getStateButton();
protected:
	//The value of pin for push up button (one when the button is pressed)
	uint8_t stateButton;

	//Register of pin
	volatile uint8_t* ddAddr;
	volatile uint8_t* portAddr;
	volatile uint8_t* pinAddr;
	uint8_t pinNo;

	//The delay to avoid the rebound
	uint16_t debounceDelay;
};



/************************************************************************/
/*                            TOGGLE BUTTON                             */
/************************************************************************/

class Toggle : public Button
{
public:
	//Use the same constuctor than Button class
	using Button::Button;
	
	//Check if button is pressed when it was not
	void refresh();
	
	//Getter for toggleValue
	uint8_t getToggleValue();
private:
	//The value of toggle button
	uint8_t toggleValue;
};



#endif /* BUTTON_H_ */