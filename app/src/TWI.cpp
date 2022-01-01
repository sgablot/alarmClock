/*
 * TWI.cpp
 *
 * Created: 31/12/2021 18:54:01
 *  Author: Sylvain
 */ 

#include "TWI.h"

#include <util/twi.h>

#define F_CPU	16000000L
#define F_SCL	100000L	//Frequency of SCL
#define TWBR_value	(((F_CPU / F_SCL) - 16) / 2)


//Initalize the frequency of TWI
void TWI_init(void)
{
	TWBR = TWBR_value;
}



//Send a START condition
uint8_t TWI_start(uint8_t addr, uint8_t w_r)
{
	//Configure the control register for send a START condition
	TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	//Wait the end of the transmission
	while(!(TWCR & (1 << TWINT))) ;
	
	//If status code is diffetnt as expected
	if((TWSR & 0xF8) != TW_START && (TWSR & 0xF8) != TW_REP_START)
	{
		//Return an error
		return 1;
	}
	
	
	//Send slave addr and write or read bit
	TWDR = (addr << 1) | w_r;
	
	//Configure the control register for send a data
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	//Wait the end of the transmission
	while(!(TWCR & (1 << TWINT))) ;
	
	
	//Check ACKNOWLEDGE
	//If the status register is diffrent from what is expected
	if((TWSR & 0xF8) != TW_MT_SLA_ACK && (TWSR & 0xF8) != TW_MR_SLA_ACK)
	{
		//Return an error
		return 1;
	}
	
	return 0;
}

//Send a STOP condition
void TWI_stop(void)
{
	//Configure the control register for send a STOP condition
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}



//Send data
uint8_t TWI_send(uint8_t data)
{
	//Stock the data into the data register
	TWDR = data;
	
	//Configure the control register for send a data
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	//Wait the end of transmission
	while(!(TWCR & (1 << TWINT))) ;
	
	
	//If the status register is different from what is expected
	if((TWSR & 0xF8) != TW_MT_DATA_ACK)
	{
		//Return an error;
		return 1;
	}
	
	return 0;
}



//Receive data and respond with an ACK
uint8_t TWI_receive_ACK(uint8_t *data)
{
	//Configure the control register for a reception with a ACK
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	
	//Wait the end of transmission
	while(!(TWCR & (1 << TWINT))) ;
	
	if((TWSR & 0xF8) != TW_MR_DATA_ACK)
	{
		//Return an error
		return 1;
	}
	
	*data = TWDR;
	
	return 0;
}

//Receive data and respond with an NACK
uint8_t TWI_receive_NACK(uint8_t *data)
{
	//Configure the control register for a reception with NACK
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	//Wait the end of transmission
	while(!(TWCR & (1 << TWINT))) ;
	
	//If the status register is different from what is expected
	if((TWSR & 0xF8) != TW_MR_DATA_NACK)
	{
		//Return an error
		return 1;
	}
	
	*data = TWDR;

	return 0;
}
