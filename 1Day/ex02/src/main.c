#include <avr/io.h>

int	main(void)
{
	DDRB |= (1 << PORTB1);

	TCCR1B |= (1 << WGM12); /* timer on */
	TCCR1A |= (1 << COM1A0); /* output is OC1A */
	TCCR1B |= ((1 << CS12)); /* scale of 256 */
	OCR1A = 31249; /* timer max */

	while (1) {
		;
	}
}
// page 142 ICR1
