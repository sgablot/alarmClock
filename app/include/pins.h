/*
 * pins.h
 *
 * Created: 29/12/2021 02:23:35
 *  Author: Sylvain
 */ 


#ifndef PINS_H_
#define PINS_H_

#define PB_ALL_ADDR	&DDRB, &PORTB, &PINB
#define PC_ALL_ADDR	&DDRC, &PORTC, &PINC
#define PD_ALL_ADDR	&DDRD, &PORTD, &PIND

#define BUTTON_PLUS_ADDR	PB_ALL_ADDR, 1
#define BUTTON_LESS_ADDR	PB_ALL_ADDR, 2
#define BUTTON_STATE_ADDR	PC_ALL_ADDR, 2
#define BUTTON_STOP_ADDR	PB_ALL_ADDR, 3
#define BUTTON_SET_ADDR		PB_ALL_ADDR, 4



#endif /* PINS_H_ */