#include <avr/io.h>

int main(void)
{
	/* page 85 - 14.2.1 */

	/* DDRB sets the direction of the pin (input/output) */
	DDRB |= (1 << DDB0); /* Here we set pin 0 to output */

	/* PORTB sets the state of a specific pin */
	PORTB |= (1 << PORTB0); /* Here we light up pin 0 */
	return 0;
}
