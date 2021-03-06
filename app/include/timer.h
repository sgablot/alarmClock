/*
 * timer.h
 *
 * Created: 29/12/2021 15:59:15
 *  Author: Sylvain
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

//Init TIMER0_8bit for 1ms
void timer_init(void);

//Getter for debounce_timer
uint16_t getDebounceTimer(void);
//debounce_timer go back to 0
void resetDebounceTimer(void);

//Getter for display_timer
uint16_t getDisplayTimer(void);

#endif /* TIMER_H_ */