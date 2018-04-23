/*
 * TX001SerialInterrup.c
 *
 * Created: 19/04/2018 11:52:14
 * Author : raulmelo-trix
 */ 

 #define F_CPU 16000000UL
 #define BAUDRATE 9600
 #define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)
 UBRR0 = BAUD_PRESCALER;// Set the baud rate prescale rate register
 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>


volatile uint8_t buffer[20];
volatile int i=0;
volatile uint8_t buffer[20];
volatile uint8_t StrRxFlag=0;

void USART_init(void)
{
	// Macro to determine the baud prescale rate see table 22.1 in the Mega datasheet
	#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)
	
	UBRR0 = BAUD_PRESCALER;         // Set the baud rate prescale rate register
	
	UCSR0C = ((0<<USBS0)|(1 << UCSZ01)|(1<<UCSZ00));   // Set frame format: 8data, 1 stop bit. See Table 22-7 for details
	UCSR0B = ((1<<RXEN0)|(1<<TXEN0));       // Enable receiver and transmitter
}

void USART_send( unsigned char data)
{
	//while the transmit buffer is not empty loop
	while(!(UCSR0A & (1<<UDRE0)));
	
	//when the buffer is empty write data to the transmitted
	UDR0 = data;
}

void USART_putstring(char* StringPtr)
// sends the characters from the string one at a time to the USART
{
	while(*StringPtr != 0x00)
	{
		USART_send(*StringPtr);
		StringPtr++;
	}
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_interrupt_init(void)
{
	cli();
	// Macro to determine the baud prescale rate see table 22.1 in the Mega datasheet
	#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)
	
	UBRR0 = BAUD_PRESCALER;                 // Set the baud rate prescale rate register
	UCSR0B = ((1<<RXEN0)|(1<<TXEN0)|(1 << RXCIE0));       // Enable receiver and transmitter and Rx interrupt
	UCSR0C = ((0<<USBS0)|(1 << UCSZ01)|(1<<UCSZ00));  // Set frame format: 8data, 1 stop bit. See Table 22-7 for details
	sei();
}

ISR(USART0_RX_vect)
{
	buffer[i]=UDR0;         //Read USART data register
	if(buffer[i++]=='\r')   //check for carriage return terminator and increment buffer index
	{
		// if terminator detected
		StrRxFlag=1;        //Set String received flag
		buffer[i-1]=0x00;   //Set string terminator to 0x00
		i=0;                //Reset buffer index
	}
}

 int main(void)
 {
	 USART_interrupt_init();   // Initailise USART 0 to use the receive interrupt
	 
	 while(1)
	 {
		 if (StrRxFlag)
		 {
			 USART_putstring(buffer);
			 USART_send('\r');           // Send carriage return
			 USART_send('\n');           // Send linefeed
			 StrRxFlag=0;                // Reset String received flag
		 }
	 }
 }