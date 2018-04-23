/**
 * \file usart.h
 * \brief usart defines and prototype of functions
 * \author Thiago - thiagosilva@trixlog.com
 * \copyright Trixlog
 * \date Creation: 06/11/2012
 * \date Change: 14/03/2013
 * \version 1.0
 */

#ifndef USART_H_
#define USART_H_
#define F_CPU 16000000 

/**
    \par API Usage Example
    The following code shows typical usage of the usart API.

    \code
    #include <avr/io.h>
    #include "usart.h"

	int main()
	{

		//Initializing usart0
  		usart0_init((ASYNC |
  			PARITY_DISABLE |
  			STOP_BIT_1 |
  			CHAR_SIZE_8),
  			9600);

  		while(1)
  		{
  			usart0_putString("Hello World!\n");
  		}

	}
\endcode */

/**
 * Includes
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

/**
 * Defines
 */
#if defined (__AVR_ATtiny2313__) || defined (__AVR_ATtiny4313__)
	#define UBRR0H		UBRRH
	#define UBRR0L  	UBRRL
	#define UCSR0C  	UCSRC
	#define UMSEL00		UMSEL
	#define UMSEL01		UMSEL
	#define UPM00		UPM0
	#define UPM01		UPM1
	#define USBS0		USBS
	#define UCSZ00		UCSZ0
	#define UCSZ01		UCSZ1
	#define UDR0		UDR
	#define UCSR0B		UCSRB
	#define UCSR0A		UCSRA
	#define UDRE0		UDRE
		#define RXCIE0	RXCIE
		#define TXCIE0	TXCIE
		#define UDRIE0	UDRIE
		#define RXEN0	RXEN
		#define TXEN0	TXEN
		#define UCSZ02	UCSZ2
		#define RXB08	RXB8
		#define TXB08	TXB8
#endif

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)  ||  defined (__AVR_ATtiny2313__ ) || defined (__AVR_ATtiny4313__)
#define	USART0_RX_vect	USART_RX_vect
#endif


#define PROGRAM_BAUDRATE				(uint16_t) (((F_CPU/16)/BAUDRATE) - 1)
#define ASYNC							(0<<UMSEL01 | 0<<UMSEL00)
#define SYNC							(0<<UMSEL01 | 1<<UMSEL00)
#define MASTER_SPI						(1<<UMSEL01 | 1<<UMSEL00)
#define PARITY_DISABLE					(0<<UPM01   | 0<<UPM00)
#define PARITY_EVEN						(1<<UPM01   | 0<<UPM00)
#define PARITY_ODD						(1<<UPM01   | 1<<UPM00)
#define STOP_BIT_1						(0<<USBS0)
#define STOP_BIT_2						(1<<USBS0)
#define CHAR_SIZE_5						(0<<UCSZ02  | 0<<UCSZ01 | 0<<UCSZ00)
#define CHAR_SIZE_6						(0<<UCSZ02  | 0<<UCSZ01 | 1<<UCSZ00)
#define CHAR_SIZE_7						(0<<UCSZ02  | 1<<UCSZ01 | 0<<UCSZ00)
#define CHAR_SIZE_8						(0<<UCSZ02  | 1<<UCSZ01 | 1<<UCSZ00)
#define CHAR_SIZE_9						(1<<UCSZ02  | 1<<UCSZ01 | 1<<UCSZ00)
#define USART0_CFG_INT_TRANSMITE		(1<<TXEN0 | 1<<UDRIE0)
#define	USART0_CFG_ENABLE_TRANSMITE		(1<<TXEN0)
#define USART0_CFG_INT_RECEIVE			(1<<RXEN0)
#define USART0_CFG_ENABLE_RECEIVE		(1<<RXEN0)

/**
 * Macros
 */
#define usart0_setBaudRate(baudrate)  	{UBRR0 = (uint16_t) (((F_CPU/16)/baudrate) - 1);}
#define usart0_setBaudRateLow(x) 		{UBRR0L = lowByte(x);}
#define usart0_setBaudRateHigh(x)		{UBRR0H = highByte(x);}
#define usart0_clear()            		{UCSR0B=0; UCSR0C=UDR0; UCSR0A=0x40; UCSR0C=0x06; UBRR0H=0; UBRR0L=0;}
#define usart0_enable()           		{UCSR0B |= ((1<<RXEN0)|(1<<TXEN0));}
#define usart0_disable()          		{UCSR0B &= ~((1<<RXEN0)|(1<<TXEN0));}
#define usart0_enableInterruptTx()		{UCSR0B |= (1<<TXEN0 | 1<<UDRIE0) ;}
#define usart0_disableInterruptTx()		{UCSR0B &= ~(1<<UDRIE0);}
#define usart0_enableInterruptRx()		{UCSR0B |= (1<<RXEN0 | 1<<RXCIE0);}
#define usart0_disableInterruptRx()		{UCSR0B &= ~(1<<RXCIE0);}
#define usart0_putData(data)			{UDR0 = data;}
#define usart0_getData()				UDR0
#define usart0_setMode(config)	 		{UCSR0C = (config);}

/**
 * Prototype of function
 */
void usart0_init(uint8_t config,uint16_t baudrate);
uint8_t usart0_getByte();
void usart0_putByte(uint8_t byte);
void usart0_putString(char* string);
void usart0_putSstringToFlash(const char *str);


#if defined (__AVR_ATtiny1634__)

/**
 * Defines
 */
#define USART1_CFG_INT_TRANSMITE		(1<<TXEN1 | 1<<UDRIE1)
#define	USART1_CFG_ENABLE_TRANSMITE		(1<<TXEN1)
#define USART1_CFG_INT_RECEIVE			(1<<RXEN1)
#define USART1_CFG_ENABLE_RECEIVE		(1<<RXEN1)

/**
 * Defines
 */
#define usart1_setBaudRate(baudrate)  	{UBRR1H = (uint8_t)((((((((uint32_t)F_CPU*1000)<<1)/((uint32_t)baudrate*8))+1)>>1)-1)>>8); \
                                  		 UBRR1L = (uint8_t)(( (((((uint32_t)F_CPU*1000)<<1)/((uint32_t)baudrate*8))+1)>>1)-1)    ; \
										}
#define usart1_setBaudRateLow(x) 		{UBRR1L = lowByte(x);}
#define usart1_setBaudRateHigh(x)		{UBRR1H = highByte(x);}
#define usart1_clear()            		{UCSR1B=0; UCSR1C=UDR1; UCSR1A=0x40; UCSR1C=0x06; UBRR1H=0; UBRR1L=0;}
#define usart1_enable()           		{UCSR1B |= ((1<<RXEN1)|(1<<TXEN1));}
#define usart1_disable()          		{UCSR1B &= ~((1<<RXEN1)|(1<<TXEN1));}
#define usart1_enableInterruptTx()		{UCSR1B |= (1<<TXEN1 | 1<<UDRIE1);}
#define usart1_disableInterruptTx()		{UCSR1B &= ~(1<<UDRIE1);}
#define usart1_enableInterruptRx()		{UCSR1B |= (1<<RXEN1 | 1<<RXCIE1);}
#define usart1_disableInterruptRx()		{UCSR1B &= ~(1<<RXCIE1);}
#define usart1_putDataU(data)			{UDR1 = data;}
#define usart1_getData()				UDR1
#define usart1_setMode(config)	 		{UCSR1C = (config);}

/**
 * Prototype of function
 */
void usart1_init(uint8_t,uint16_t);
void usart1_putByte(uint8_t byte);
void usart1_putString(char* string);
void usart1_putSstringToFlash(const char *str);

#endif

#endif /* USART_H_ */
