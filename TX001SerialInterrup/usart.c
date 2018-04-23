/**
 * \file usart.c
 * \brief usart functions implementation
 * \author Thiago - thiagosilva@trixlog.com
 * \copyright Trixlog
 * \date Creation: 06/11/2012
 * \date Change: 14/03/2013
 * \version 1.0
 */

/**
 * Includes
 */
#include "usart.h"

/**
 * Definition of functions
 */

/**
 * \fn usart0_init(config,baudrate)
 * \brief Configurate usart0
 * \param config(variable type uint8_t), baudrate(variable type uint16_t)
 * \return void
 */
void usart0_init(uint8_t config,uint16_t baudrate)
{
	usart0_setBaudRate(baudrate);
	usart0_setMode(config);
	usart0_enable();
}

uint8_t usart0_getByte( void )
{
	uint8_t data, status;
	while(!(UCSR0A & (1<<RXC0))); 	// Wait for incomming data
	status = UCSR0A;
	data = UDR0;
	return(data);
}

/**
 * \fn usart0_putByte(byte)
 * \brief Write a byte in usart0
 * \param byte(variable type uint8_t)
 * \return void
 */
void usart0_putByte(uint8_t byte)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = byte;
}

/**
 * \fn usart0_putByte(string)
 * \brief Write a string in usart0
 * \param string(variable type uint8_t pointer)
 * \return void
 */
void usart0_putString(char* string)
{
	while (*string)
	{
		usart0_putByte(*string++);
	}
}

ISR(USART_RX_vect) {

}

/**
 * \fn ISR(vect)
 * \brief Interrupt received data usart0
 * \param interrupt vector
 * \return void
 */


#if defined (__AVR_ATtiny1634__)

/**
 * \fn usart1_init(config,baudrate)
 * \brief Configurate usart1
 * \param config(variable type uint8_t), baudrate(variable type uint16_t)
 * \return void
 */
 void usart1_init(uint8_t config,uint16_t baudrate)
 {
 	usart1_setBaudRate((((F_CPU/16)/baudrate) - 1));
 	usart1_setMode(config);
 	usart1_enable();
 }


 /**
  * \fn usart1_putByte(byte)
  * \brief Write a byte in usart1
  * \param byte(variable type uint8_t)
  * \return void
  */
 void usart1_putByte(uint8_t byte)
 {
 	while (!(UCSR1A & (1 << UDRE1)));
 	UDR1 = byte;
 }

 /**
  * \fn usart1_putByte(string)
  * \brief Write a string in usart1
  * \param string(variable type uint8_t pointer)
  * \return void
  */
 void usart1_putString(char* string)
 {
 	while (*string)
 	{
 		usart1_putByte(*string++);
 	}
 }


 /**
  * \fn ISR(vect)
  * \brief Interrupt received data usart1
  * \param interrupt vector
  * \return void
  */

#endif
