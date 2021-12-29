/*
 * alarmClock.cpp
 *
 * Created: 29/12/2021 00:53:24
 * Author : Sylvain
 */ 

#define F_CPU 16000000L

#include <avr/io.h>

#include "pins.h"
#include "button.h"

//Test with led pin 13 arduino
#define LED_INIT()	DDRB |= (1 << DDB5)
#define LED_ON()	PORTB |= (1 << PORTB5)
#define LED_OFF()	PORTB &= ~(1 << PORTB5)

Toggle button_set = Toggle(BUTTON_STATE_ADDR, 200);

int main(void)
{	
	button_set.init();
	LED_INIT();
	
	while (1)
	{
		button_set.refresh();
		if(button_set.getToggleValue())
		{
			LED_ON();
		}
		else
		{
			LED_OFF();
		}
	}
}

