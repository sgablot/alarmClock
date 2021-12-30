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
#include "timer.h"
#include "display.h"

//Test with led pin 13 arduino
#define LED_INIT()	DDRB |= (1 << DDB5)
#define LED_ON()	PORTB |= (1 << PORTB5)
#define LED_OFF()	PORTB &= ~(1 << PORTB5)

int main(void)
{	
	button_init();
	timer_init();
	display_init();

	LED_INIT();
	
	while (1)
	{
		button_refresh();
		if(button_state.getToggleValue())
		{
			LED_ON();
		}
		else
		{
			LED_OFF();
		}
		
		display_classicDisplay();
		display_refresh();
	}
}

