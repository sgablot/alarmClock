/*
 * RTC.cpp
 *
 * Created: 01/01/2022 00:26:28
 *  Author: Sylvain
 */ 

#include "RTC.h"

#include "TWI.h"

#define DS1307_ADDR	0b1101000

//TODO add error management

//For all instruction view the Table 2. Timekeeper Registers

/************************************************************************/
/*                           PUBLIC FUNCTION                            */
/************************************************************************/

//Initialize the DS1307 / TWI
void RTC_init()
{
	TWI_init();
}



//Start the clock
void RTC_startClock()
{
	//cf. Figure 4. Data Write - Slave Receiver Mode
	TWI_start(DS1307_ADDR, WRITE);
	TWI_send(0x00);
	//Define the second to 0 with the CH bit to 0
	TWI_send(0x00);
	TWI_stop();
}

//Stop the clock
void RTC_stopClock()
{
	//cf. Figure 4. Data Write - Slave Receiver Mode
	TWI_start(DS1307_ADDR, WRITE);
	TWI_send(0x00);
	//Set the CH bit to 1
	TWI_send(0x80);
	TWI_stop();
}



//Get the clock of RTC
DateTime RTC_getClock(void)
{
	//cf. Figure 6. Data Read (Write Pointer, Then Read) - Slave Receive and Transmit | DS1307_datasheet
	DateTime time;
	TWI_start(DS1307_ADDR, WRITE);
	//The address of clock
	TWI_send(0x00);
	TWI_start(DS1307_ADDR, READ);
	time.seconds = bcd_to_int(TWI_receive_ACK());
	time.minutes = bcd_to_int(TWI_receive_ACK());
	time.hours = bcd_to_int(TWI_receive_NACK());
	TWI_stop();
	return time;
}

//Get the alarm of RTC
DateTime RTC_getAlarm(void)
{
	//cf. Figure 6. Data Read (Write Pointer, Then Read) - Slave Receive and Transmit | DS1307_datasheet
	DateTime time;
	TWI_start(DS1307_ADDR, WRITE);
	//The address of alarm
	TWI_send(0x0A);
	TWI_start(DS1307_ADDR, READ);
	time.minutes = bcd_to_int(TWI_receive_ACK());
	time.hours = bcd_to_int(TWI_receive_NACK());
	TWI_stop();
	return time;	
}



//Set the clock of RTC
void RTC_setClock(DateTime time)
{
	//cf. Figure 4. Data Write - Slave Receiver Mode
	TWI_start(DS1307_ADDR, WRITE);
	TWI_send(0x00);
	//For set the CH bit in addr 0x00 for stop the clock
	TWI_send(int_to_bcd(time.seconds) | 0x80);
	TWI_send(int_to_bcd(time.minutes));
	TWI_send(int_to_bcd(time.hours));
	TWI_stop();
}

//Set the alarm of RTC
void RTC_setAlarm(DateTime time)
{
	//cf. Figure 4. Data Write - Slave Receiver Mode
	TWI_start(DS1307_ADDR, WRITE);
	TWI_send(0x0A);
	//For set the SET bit in addr 0x0A (Bit7)
	TWI_send(int_to_bcd(time.minutes) | 0x80);
	TWI_send(int_to_bcd(time.hours));
	TWI_stop();
}



//Add a minute to clock or alarm
void RTC_addMinute(uint8_t whichClock)
{
	//If whichClock equal 1 then get the value of clock else get the value of alarm
	DateTime time = whichClock ? RTC_getClock() : RTC_getAlarm();
	
	if(time.minutes + 1 >= 60)
	{
		if(time.hours + 1 >= 24)
		{
			time.hours = 0;
		}
		else
		{
			time.hours++;
		}
		time.minutes = 0;
	}
	else
	{
		time.minutes++;
	}
	
	//If whichClock equal 1 then set the clock with the new value else set the alarm with the new value
	whichClock ? RTC_setClock(time) : RTC_setAlarm(time);
}

//Substract a minute to clock or alarm
void RTC_substractMinute(uint8_t whichClock)
{
	//If whichClock equal 1 then get the value of clock else get the value of alarm
	DateTime time = whichClock ? RTC_getClock() : RTC_getAlarm();
	
	if(time.minutes - 1 <= 0)
	{
		if(time.hours - 1 <= 0)
		{
			time.hours  = 23;
		}
		else
		{
			time.hours--;
		}
		time.minutes = 59;
	}
	else
	{
		time.minutes--;
	}
	
	//If whichClock equal 1 then set the clock with the new value else set the alarm with the new value
	whichClock ? RTC_setClock(time) : RTC_setAlarm(time);
}



//Check if the clock equal to alarm
uint8_t RTC_clockEqualAlarm(void)
{
	//If clock equal to alarm then return 1 else return 0
	if(RTC_getAlarm() == RTC_getClock())	return 1;
	return 0;
}
