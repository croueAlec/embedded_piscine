#include <avr/io.h>

int	main(void)
{
	DDRB |= (1 << PORTB1);

	TCCR1B |= (1 << WGM12); /* Here we turn on the timer */

	/* page 140 - 16.11.1 */
	TCCR1A |= (1 << COM1A0); /* Here tell the timer to toggle OC1A (PORTB1) on compare match */

	OCR1A = 15624;
	TCCR1B |= ((1 << CS12));

	while (1) {
		;
	}
}
