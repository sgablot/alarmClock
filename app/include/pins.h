/*
 * pins.h
 *
 * Created: 29/12/2021 02:23:35
 *  Author: Sylvain
 */ 


#ifndef PINS_H_
#define PINS_H_

//GLOBAL METHODE
inline void DEFINE_OUTPUT_PIN(volatile uint8_t* ddAddr, volatile uint8_t* portAddr, volatile uint8_t* pinAddr, uint8_t pinNo)	{ *ddAddr |= (1 << pinNo); }
inline void SET_PIN_LOW(volatile uint8_t* ddAddr, volatile uint8_t* portAddr, volatile uint8_t* pinAddr, uint8_t pinNo)	{ *portAddr &= ~(1 << pinNo); }
inline void SET_PIN_HIGH(volatile uint8_t* ddAddr, volatile uint8_t* portAddr, volatile uint8_t* pinAddr, uint8_t pinNo)	{ *portAddr |= (1 << pinNo); }

inline volatile uint8_t* GET_PORT(volatile uint8_t* ddAddr, volatile uint8_t* portAddr, volatile uint8_t* pinAddr, uint8_t pinNo)	{ return portAddr; }
inline uint8_t GET_PIN(volatile uint8_t* ddAddr, volatile uint8_t* portAddr, volatile uint8_t* pinAddr, uint8_t pinNo)		{ return pinNo; }


#define PB_ALL_ADDR	&DDRB, &PORTB, &PINB
#define PC_ALL_ADDR	&DDRC, &PORTC, &PINC
#define PD_ALL_ADDR	&DDRD, &PORTD, &PIND

//BUTTON
#define BUTTON_PLUS_ADDR	PB_ALL_ADDR, 1
#define BUTTON_LESS_ADDR	PB_ALL_ADDR, 2
#define BUTTON_STATE_ADDR	PC_ALL_ADDR, 2
#define BUTTON_STOP_ADDR	PB_ALL_ADDR, 3
#define BUTTON_SET_ADDR		PB_ALL_ADDR, 4


//DISPLAY
//8Bit Shifter
#define DATA_PIN	PD_ALL_ADDR, 2
#define LATCH_PIN	PD_ALL_ADDR, 3
#define CLOCK_PIN	PD_ALL_ADDR, 4
//7Segment 4Digits
#define FIRST_DIGIT_PIN		PD_ALL_ADDR, 5
#define SECOND_DIGIT_PIN	PD_ALL_ADDR, 6
#define THIRD_DIGIT_PIN		PD_ALL_ADDR, 7
#define FOURTH_DIGIT_PIN	PB_ALL_ADDR, 0


#endif /* PINS_H_ */