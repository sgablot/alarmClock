/*
 * timer.cpp
 *
 * Created: 29/12/2021 15:59:07
 *  Author: Sylvain
 */ 

#include "timer.h"

static uint16_t debounce_timer = 0;

//When the timer overflow
ISR(TIMER0_OVF_vect)
{
	//Add 1 every 1ms
	debounce_timer++;
}

//Init TIMER0_8bit for 1ms
void timer_init(void)
{
	//Enable Fast PWM for Timer
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << WGM02);
	
	//Define 64 prescaler
	TCCR0B |= (1 << CS01) | (1 << CS00);
	
	//Define the top of timer (when it overflow) -> 250 cycle with 16Mhz frenquency and a 64 prescaler = 1ms overflow
	OCR0A = 250;
	
	//Enable Timer Overflow Interrupt
	TIMSK0 |= (1 << TOIE0);
	
	//Enable Interrupt
	sei();
}


//Getter for debounce_timer
uint16_t getDebounceTimer(void)
{
	return debounce_timer;
}
//debounce_timer go back to 0
void resetDebounceTimer(void)
{
	debounce_timer = 0;
}

