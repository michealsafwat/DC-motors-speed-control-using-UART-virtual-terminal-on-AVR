/*
 * MACROS_AND_UART.c
 *
 * Created: 8/24/2021 5:13:32 AM
 *  Author: Micheal
 */ 


#include "MACROS_AND_UART.h"

 unsigned char string[13];			// this array holds the data frame used by the UART “AXXXBXXXCXXX” and the terminating char at the end 

void USART_Init()
{
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}


//Receive a character through UART
unsigned char  UART0_Rx_Char()
{
	//wait for the character to be received
	while(!(UCSR0A & (1<<RXC0)));				// check if the buffer is empty(ready to receive), RXC0 is cleared when ready to receive

	//return the received character
	return(UDR0);						      //UDR0 is the register that is used to receive and store data
}



//Receive string through UART
 unsigned char * UART0_Rx_Str()
{
	
unsigned char x, i = 0;
	//receive the characters until ENTER is pressed (ASCII for ENTER = 13)
	while((x = UART0_Rx_Char()) != 13)
	{
		//and store the received characters into the array string[] one-by-one
		string[i++] = x;
	}

	//insert NULL to terminate the string
	string[i] = '\0';

	//return the received string
	return(string);
}
