/*
 * display.h
 *
 * Created: 29/12/2021 22:39:49
 *  Author: Sylvain
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#define F_CPU 16000000L

#include <util/delay.h>

#include <avr/io.h>
#include "timer.h"
#include "pins.h"


/************************************************************************/
/*                           PUBLIC FUNCTION                            */
/************************************************************************/

//Initialize all pins for the display (8Bit Shifter / 7Segment4Digits)
void display_init(void);

//Show clock during 50s and show temperature during 10s
void display_classicDisplay(void);
//Show clock with blinking
void display_showClockWBlinking(void);
//Show alarm clock with blinking
void display_showAlarmWBlinking(void);
//Show ERROR
void display_showError(void);

//Refresh the display
void display_refresh(void);


#endif /* DISPLAY_H_ */