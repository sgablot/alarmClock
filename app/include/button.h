/*
 * button.h
 *
 * Created: 29/12/2021 01:07:07
 *  Author: Sylvain
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>
#include "pins.h"

/************************************************************************/
/*                             PUSH BUTTON                              */
/************************************************************************/

class Button
{
public:
	//Constructor for the button: register address and pin number
	Button(volatile uint8_t* ddAddr, volatile uint8_t* portAddr, volatile uint8_t* pinAddr, uint8_t pinNo);
	
	//Initilize register for pullup input
	void init(void);
	//Read the state of the button
	void refresh(void);
	
	//Getter for stateButton
	uint8_t getStateButton(void);
	
	//Return 1 when state of button go LOW to HIGH
	uint8_t isPressed(void);
	//Return 1 when state of button go HIGH to LOW
	uint8_t isReleased(void);
	
protected:
	//The value of pin for push up button (one when the button is pressed)
	uint8_t stateButton;
	//The old state of button
	uint8_t lastState;

	//Register of pin
	volatile uint8_t* ddAddr;
	volatile uint8_t* portAddr;
	volatile uint8_t* pinAddr;
	uint8_t pinNo;
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
	void refresh(void);
	
	//Getter for toggleValue
	uint8_t getToggleValue(void);
	
private:
	//The value of toggle button
	uint8_t toggleValue;
};



/************************************************************************/
/*                          BUTTON DECLARATION                          */
/************************************************************************/

extern Button button_plus;
extern Button button_less;
extern Toggle button_state;
extern Button button_stop;
extern Button button_set;



/************************************************************************/
/*                        BUTTON GLOBAL FUNCTION                        */
/************************************************************************/

//Function for initialize all buttons
void button_init(void);

//Function for refresh all buttons with debounce system
void buttons_refresh(void);



#endif /* BUTTON_H_ */