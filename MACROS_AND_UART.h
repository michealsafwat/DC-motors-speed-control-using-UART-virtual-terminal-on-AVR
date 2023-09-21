/*
 * MACROS_AND_UART.h
 *
 * Created: 8/24/2021 5:11:00 AM
 *  Author: Micheal
 */ 


#ifndef MACROS_AND_UART_H_
#define MACROS_AND_UART_H_


#define F_CPU 16000000UL // Defining the CPU Frequency

#include <avr/io.h>      // Contains all the I/O Register Macros
#include <string.h>
#include<stdio.h>
#include<stdlib.h>

#define USART_BAUDRATE 9600 // Desired Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection

#define DISABLED    (0<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection


#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection

#define	Mapped_Speed_A					(SPEED_A*(255/100))
#define	Mapped_Speed_B					(SPEED_B*(255/100))
#define	Mapped_Speed_C					(SPEED_C*(255/100))


void USART_Init();

unsigned char  UART0_Rx_Char();

#endif /* MACROS_AND_UART_H_ */