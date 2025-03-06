#include <avr/io.h>
#include <ctype.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "emb.h"

void	uart_init()
{
	/* page 185 - 20.5 */
	UBRR0L = (uint8_t)((UBRRN) & 0xFF); /* Lower half of Baud Rate */
	UBRR0H = (uint8_t)((UBRRN) >> 8); /* Upper rate of Baud Rate */

	/* page 185 - 20.6  also page 201 - 20.11.3*/
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); /* Enable Receive and Transmit */

	/* page 182 - 20.3.2 */
	UCSR0A |= (1 << U2X0); /* Enabling double transfer speed, and divide by two baudrate */

	/* page 202 - 20.11.4 & 20-11*/
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); /* set transmission bit size */
}

void	uart_tx(char c)
{
	/* page 186 - 20.6.1 */
	while (!(UCSR0A & (1 << UDRE0))) /* Wait for empty buffer */
		;
	UDR0 = c; /* Set data in buffer */
}

ISR(USART_RX_vect) /* Behavior of USART Receive */
{
	char	c = UDR0;

	if (isupper(c)) {
		c = tolower(c);
	} else if (islower(c)) {
		c = toupper(c);
	}

	uart_tx(c);
}

int	main(void)
{
	uart_init();

	UCSR0B |= (1 << RXCIE0); /* Enable receive interrupt */

	sei();

	while (1) {
		;
	}
}
