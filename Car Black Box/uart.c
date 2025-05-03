#include <xc.h>
#include "uart.h"
#include "main.h"

void init_uart(void)
{
	/* Serial initialization */
	RX_PIN = 1;
	TX_PIN = 0;

	/* TXSTA:- Transmitor Status and control Register */
	/* 9bit TX enable or disable bit */ 
	TX9 = 0;  //*for enabling 8 bit register
	/* UART Tarsmition enable bit */
	TXEN = 1;  //*if it 0 not able to transmit the data
	/* Synchronous or Asynchronous mode selection */
	/* Asynchronous */
	SYNC = 0;  //*asyncronous mode -> no need to set bit7,if its 1-> syncronous protocol ie. master and slave 
	/* Send the Break character bit */
	SENDB = 0;  //*10=it send break bit autometically after sending the data  to identify next set of data ,if its-> 1 we have to send the break bit along with data
	/* Low or High baud rate selection bit */
	/* High Baud Rate */
	BRGH = 1;     //*1=high speed ,0=low speed  

	/* RCSTA :- Recepition Status and control Register */
	/* TX/RC7 and RX/RC6 act as serial port */ 
	SPEN = 1;
	/* 9bit RX enable or disable bit */
	RX9 = 0; //*for enabling 8 bit register
	/* Continous reception enable or disable */ 
	CREN = 1;

	/* BAUDCTL:- Baud rate control register */

	/* 16bit baud generate bit */ 
    
    //*ABDOVF=0;
	BRG16 = 0;//* 8 bit baud rate generate
	
    //*Wake up enble bit
   //* WUE=0;
            
    //*auto baud enable bit
   //* ABDEN=0;
    
	/* Baud Rate Setting Register */
	/* Set to 10 for 115200, 64 for 19200 and 129 for 9600 */
	SPBRG = 129;


	/* TX interrupt flag bit */
	TXIF = 0;

	/* RX interrupt enable bit */
	RCIF = 0;
}

void putch(unsigned char byte) 
{
	/* Output one byte */
	/* Set when register is empty */
	while(!TXIF)
	{
		continue;
	}
	TXIF = 0;
	TXREG = byte;
} 

int puts(const char *s)
{
	while(*s)		
	{
	 putch(*s++);	
	}
	return 0;
}

unsigned char getch(void)
{
	/* Retrieve one byte */
	/* Set when register is not empty */
	while(!RCIF)
	{
		continue;
	}
	RCIF = 0;
	return RCREG;
}

unsigned char getche(void)
{
	unsigned char c;

	putch(c = getch());

	return (c);
}
