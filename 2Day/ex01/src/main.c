#include <avr/io.h>
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

void uart_printstr(const char *str)
{
	while (*str) {
		uart_tx(*str++);
	}
}

ISR(TIMER1_COMPA_vect) /* Behavior of Timer1 interrupt */
{
	uart_printstr("Hello World!\r\n");
}

int	main(void)
{
	uart_init();

	TCCR1B |= (1 << WGM12);

	TIMSK1 |= (1 << OCIE1A );

	sei();

	/* since we need to go from 1Hz to 0.5Hz
	the previous prescaler can't do that
	we go to the next prescaler (from 256 to 1024)
	now we have 4x the previous range so with 62499 we would be at 0.25Hz
	thus we need to divide 62499 by 2 to get our new TOP
	*/
	OCR1A = 31249;
	TCCR1B |= (1 << CS12) | (1 << CS10); /* 1024 prescaler */

	while (1) {
		;
	}
}
