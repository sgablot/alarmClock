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
#include "TWI.h"
#include "RTC.h"

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
	
	TWI_init();
	
	while (1)
	{
		buttons_refresh();
		
		if(button_set.isPressed())
		{
			RTC_stopClock();
		}
		else if(button_set.isReleased())
		{
			RTC_startClock();
		}
		
		if(button_set.getStateButton() && button_state.getStateButton())
		{
			display_showError();
		}
		else if(button_set.getStateButton())
		{
			if(button_plus.getStateButton())
			{
				RTC_addMinute(1);
			}
			else if(button_less.getStateButton())
			{
				RTC_substractMinute(1);
			}
			display_showClockWBlinking();
		}
		else if(button_state.getStateButton())
		{
			if(button_plus.getStateButton())
			{
				RTC_addMinute(0);
			}
			else if(button_less.getStateButton())
			{
				RTC_substractMinute(0);
			}
			display_showAlarmWBlinking();
		}
		else
		{
			display_classicDisplay();
		}
		
		
		display_refresh();
	}
}

