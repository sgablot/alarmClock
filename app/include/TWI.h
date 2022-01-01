/*
 * TWI.h
 *
 * Created: 31/12/2021 18:54:10
 *  Author: Sylvain
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>

#define WRITE	0
#define READ	1


//Initalize the frequency of TWI
void TWI_init(void);

//Send a START condition
uint8_t TWI_start(uint8_t addr, uint8_t w_r);
//Send a STOP condition
void TWI_stop(void);

//Send data
uint8_t TWI_send(uint8_t data);

//Receive data and respond with an ACK
uint8_t TWI_receive_ACK(void);
//Receive data and respond with an NACK
uint8_t TWI_receive_NACK(void);

#endif /* TWI_H_ */