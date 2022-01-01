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

/************************************************************************/
/*                           PUBLIC FUNCTION                            */
/************************************************************************/

//Initialize the DS1307 / TWI
void RTC_init()
{
	TWI_init();
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


//Check if the clock equal to alarm
uint8_t RTC_clockEqualAlarm(void)
{
	//If clock equal to alarm then return 1 else return 0
	if(RTC_getAlarm() == RTC_getClock())	return 1;
	return 0;
}



/************************************************************************/
/*                           PRIVATE FUNCTION                           */
/************************************************************************/

//Convert a BCD number into a int number
static uint8_t bcd_to_int(uint8_t data) { return ((data >> 4) * 10) + (data & 0x0F); }
//Convert a int number into a BCD number
static uint8_t int_to_bcd(uint8_t data) { return ((data / 10) << 4) | (data % 10); }
