/*
 * RTC.h
 *
 * Created: 01/01/2022 00:26:20
 *  Author: Sylvain
 */ 


#ifndef RTC_H_
#define RTC_H_

#include <time.h>

//Create a struct for stock the value of hours, minutes and second all at once
typedef struct 
{
	uint8_t hours = 0;
	uint8_t minutes = 0;
	uint8_t seconds = 0;
} DateTime;

//Create operator== for compare DateTime with DateTime
inline bool operator==(const DateTime &a, const DateTime &b)
{
	return ((a.hours == b.hours) && (a.minutes == b.minutes) && (a.seconds == b.seconds)) ? 1 : 0 ;
}


/************************************************************************/
/*                           PUBLIC FUNCTION                            */
/************************************************************************/

//Initialize the DS1307 / TWI
void RTC_init();


//Start the clock
void RTC_startClock();
//Stop the clock
void RTC_stopClock();


//Get the clock of RTC
DateTime RTC_getClock(void);
//Get the alarm of RTC
DateTime RTC_getAlarm(void);


//Set the clock of RTC
void RTC_setClock(DateTime time);
//Set the alarm of RTC
void RTC_setAlarm(DateTime time);


//Add a minute to clock or alarm
void RTC_addMinute(uint8_t whichClock);
//Substract a minute to clock or alarm
void RTC_substractMinute(uint8_t whichClock);


//Check if the clock equal to alarm
uint8_t RTC_clockEqualAlarm(void);



/************************************************************************/
/*                           PRIVATE FUNCTION                           */
/************************************************************************/

//Convert a BCD number into a int number
static uint8_t bcd_to_int(uint8_t data) { return ((data >> 4) * 10) + (data & 0x0F); }
//Convert a int number into a BCD number
static uint8_t int_to_bcd(uint8_t data) { return ((data / 10) << 4) | (data % 10); }


#endif /* RTC_H_ */