#include <avr/io.h>

int	main(void)
{
	DDRB |= (1 << PORTB1);

	/* page 131 - 16.9.2 */
	TCCR1B |= (1 << WGM12); /* Here we turn on the timer */

	/* page 140 - 16.11.1 */
	TCCR1A |= (1 << COM1A0); /* Here tell the timer to toggle OC1A (PORTB1) on compare match */

	/* page 142 - 16.11.2 & 16-5*/
	TCCR1B |= ((1 << CS12)); /* Here we set the prescaler to a scale of 256 */

	/* Formula : (F_CPU / (PRESCALE * FREQUENCY)) - 1 */
	OCR1A = 31249; /* = (16,000,000 / (256 * 2)) - 1 */

	while (1) {
		;
	}
}
