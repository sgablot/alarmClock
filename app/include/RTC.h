/*
 * RTC.h
 *
 * Created: 01/01/2022 00:26:20
 *  Author: Sylvain
 */ 


#ifndef RTC_H_
#define RTC_H_

#include <time.h>

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


//Get the clock of RTC
DateTime RTC_getClock(void);
//Get the alarm of RTC
DateTime RTC_getAlarm(void);


//Set the clock of RTC
void RTC_setClock(DateTime time);
//Set the alarm of RTC
void RTC_setAlarm(DateTime time);


//Check if the clock equal to alarm
uint8_t RTC_clockEqualAlarm(void);



/************************************************************************/
/*                           PRIVATE FUNCTION                           */
/************************************************************************/

//Convert a BCD number into a int number
static uint8_t bcd_to_int(uint8_t data);
//Convert a int number into a BCD number
static uint8_t int_to_bcd(uint8_t data);


#endif /* RTC_H_ */