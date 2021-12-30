/*
 * display.cpp
 *
 * Created: 29/12/2021 22:39:38
 *  Author: Sylvain
 */ 

#include "display.h"

#define LATCH_LOW()		SET_PIN_LOW(LATCH_PIN);
#define LATCH_HIGH()	SET_PIN_HIGH(LATCH_PIN);

#define CLOCK_LOW()		SET_PIN_LOW(CLOCK_PIN);
#define CLOCK_HIGH()	SET_PIN_HIGH(CLOCK_PIN);

#define DATA_LOW()		SET_PIN_LOW(DATA_PIN);
#define DATA_HIGH()		SET_PIN_HIGH(DATA_PIN);


static void printClock();
static void printAlarm();
static void printTemperature();

static void printDigit(volatile uint8_t* portAddr, uint8_t pinNo, uint8_t segment);

/************************************************************************/
/*                            LOCAL VARIABLE                            */
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
	digits.digit0 = encode[1];
	digits.digit1 = encode[2];
	digits.digit2 = encode[4];
	digits.digit3 = encode[5];
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

static void printClock();
static void printAlarm();
static void printTemperature();

static void printDigit(volatile uint8_t* portAddr, uint8_t pinNo, uint8_t segment)
{
	//Turn off DIGITx
	*portAddr &= ~(1 << pinNo);
	
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
