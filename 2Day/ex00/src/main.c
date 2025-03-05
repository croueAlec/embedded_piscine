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

	/* Example :
		UBRRN = 0110 1001
					&1111
		UBRR0L		 1001

		UBRRN = 0110 1001
				 >>8 0110
		UBRR0H		 0110
	*/

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

/* page 66 - 12-1 */
ISR(TIMER1_COMPA_vect) /* Behavior of Timer1 interrupt */
{
	uart_tx('Z');
}

int	main(void)
{
	uart_init();

	TCCR1B |= (1 << WGM12); /* Timer1 CTC mode */

	/* page 145 - 16.11.8 */
	TIMSK1 |= (1 << OCIE1A ); /* Enable interrupt when OCF1A bit is set upon Timer Compare Match */

	sei(); /* Set global interrupts */

	OCR1A = 62499;
	TCCR1B |= (1 << CS12);

	while (1) {
		;
	}
}
