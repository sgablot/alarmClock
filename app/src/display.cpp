/*
 * display.cpp
 *
 * Created: 29/12/2021 22:39:38
 *  Author: Sylvain
 */ 

#include "display.h"

//for abs() function
#include <stdlib.h>
#include "TWI.h"
#include "RTC.h"

#define LATCH_LOW()		SET_PIN_LOW(LATCH_PIN);
#define LATCH_HIGH()	SET_PIN_HIGH(LATCH_PIN);

#define CLOCK_LOW()		SET_PIN_LOW(CLOCK_PIN);
#define CLOCK_HIGH()	SET_PIN_HIGH(CLOCK_PIN);

#define DATA_LOW()		SET_PIN_LOW(DATA_PIN);
#define DATA_HIGH()		SET_PIN_HIGH(DATA_PIN);

#define DISPLAY_NOTHING	0x00
#define DISPLAY_MINUS	0x02
#define DISPLAY_DEGREE	0xC6

#define DS1307_ADDR		0b1101000

/************************************************************************/
/*                 LOCAL VARIABLE & FUNCTION DEFINITION                 */
/************************************************************************/

//Struct for stock the value of each digit and colon
typedef struct {
	uint8_t digit0;
	uint8_t digit1;
	uint8_t digit2;
	uint8_t digit3;
	
	uint8_t colon;
} Digits;

Digits digits = {0, 0, 0, 0, 0};

//Array for encode number into segment to display
char encode[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};


//LOCAL FUNCTION DEFINITION
static void printClock(uint8_t hours, uint8_t minutes);
static void printAlarm(uint8_t hours, uint8_t minutes);
static void printNothing();
static void printTemperature(int8_t temperature);

static void printDigit(volatile uint8_t* portAddr, uint8_t pinNo, uint8_t segment);



/************************************************************************/
/*                           PUBLIC FUNCTION                            */
/************************************************************************/

//Initialize all pins for the display (8Bit Shifter / 7Segment4Digits)
void display_init(void)
{
	//Define all port as output
	DEFINE_OUTPUT_PIN(DATA_PIN);
	DEFINE_OUTPUT_PIN(LATCH_PIN);
	DEFINE_OUTPUT_PIN(CLOCK_PIN);
	
	DEFINE_OUTPUT_PIN(FIRST_DIGIT_PIN);
	DEFINE_OUTPUT_PIN(SECOND_DIGIT_PIN);
	DEFINE_OUTPUT_PIN(THIRD_DIGIT_PIN);
	DEFINE_OUTPUT_PIN(FOURTH_DIGIT_PIN);
}


//Show clock during 50s and show temperature during 10s
void display_classicDisplay(void)
{
	if(/*seconde du DS1307 >= 50*/1)
	{
		//Afficher la temperature
	}
	else
	{
		//Afficher l'heure
	}
	
	//TEST
	
	DateTime time = RTC_getClock();
	
	printClock(time.minutes, time.seconds);
	
	//printTemperature(-15);
}


//Refresh the display
void display_refresh(void)
{
	printDigit(GET_PORT(FIRST_DIGIT_PIN), GET_PIN(FIRST_DIGIT_PIN), digits.digit0);
	printDigit(GET_PORT(SECOND_DIGIT_PIN), GET_PIN(SECOND_DIGIT_PIN), digits.digit1);
	printDigit(GET_PORT(THIRD_DIGIT_PIN), GET_PIN(THIRD_DIGIT_PIN), digits.digit2);
	printDigit(GET_PORT(FOURTH_DIGIT_PIN), GET_PIN(FOURTH_DIGIT_PIN), digits.digit3);
}



/************************************************************************/
/*                           PRIVATE FUNCTION                           */
/************************************************************************/

//Convert hours and minutes into digits to be display
static void printClock(uint8_t hours, uint8_t minutes)
{
	//Get the ten of hours
	if(hours >= 10)
	{
		digits.digit0 = encode[hours / 10];
	}
	else
	{
		//If the ten of hours == 0 then display nothing
		digits.digit0 = DISPLAY_NOTHING;
	}
	
	//Get the units of the hours
	digits.digit1 = encode[hours % 10];
	

	//Get the ten of minutes
	digits.digit2 = encode[minutes / 10];
	//Get the units of mintues
	digits.digit3 = encode[minutes % 10];

	//Display the colon separator
	digits.colon = true;
}

//Same thing than display clock but add a dot on second to last digit
static void printAlarm(uint8_t hours, uint8_t minutes)
{
	printClock(hours, minutes);
	
	//Add a dot on second to last digits
	digits.digit2 |= 1;
}

//Display nothing on all digits
static void printNothing()
{
	digits.digit0 = DISPLAY_NOTHING;
	digits.digit1 = DISPLAY_NOTHING;
	digits.digit2 = DISPLAY_NOTHING;
	digits.digit3 = DISPLAY_NOTHING;
	digits.colon = false;
}

//Convert a temperature into digits to be display with sign minus or not and with degree sign
static void printTemperature(int8_t temperature)
{
	//Variable for stock if temperature is negative
	uint8_t neg = false;
	
	//For save the negative and get absolute temperature for the rest processes
	if(temperature < 0)
	{
		neg = true;
		temperature = abs(temperature);
	}
	else
	{
		digits.digit0 = DISPLAY_NOTHING;
	}
	
	if(temperature >= 10)
	{
		//If temperature is negative, display the minus sign else display nothing
		digits.digit0 = (neg == 1) ? DISPLAY_MINUS : DISPLAY_NOTHING;
		//Get and encode the ten of temperature
		digits.digit1 = encode[temperature / 10];
	}
	else
	{
		//Dipslay minus sign on second digit if temperature is negative and contain no ten
		digits.digit1 = (neg==1) ? DISPLAY_MINUS : DISPLAY_NOTHING;
	}
	
	//Get and encode the units of temperature
	digits.digit2 = encode[temperature % 10];
	//Display the ° symbol
	digits.digit3 = DISPLAY_DEGREE;
	
	//Disable the colon sperator
	digits.colon = false;
}


//Display digitX
static void printDigit(volatile uint8_t* portAddr, uint8_t pinNo, uint8_t segment)
{
	//8Bit Shifter
	
	LATCH_LOW();
	
	for (uint8_t i = 0; i < 8; i++)
	{
		CLOCK_LOW();
		
		//If segment x must be displayed then set data to 0 / LOW
		uint8_t data = ((~segment >> i) & 1);
		
		
		if(data)	{ DATA_HIGH(); }
		else		{ DATA_LOW(); }
			
		CLOCK_HIGH();
	}
	
	//Push data on pins
	LATCH_HIGH();
	
	//Turn on digit during Xµs
	*portAddr |= (1 << pinNo);
	_delay_us(1000);
	*portAddr &= ~(1 << pinNo);
}
