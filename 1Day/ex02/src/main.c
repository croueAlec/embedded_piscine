#include <avr/io.h>

int	main(void)
{
	DDRB |= (1 << PORTB1);

	/* page 140 - 16-2 we now set it to clear on match*/
	TCCR1A |= (1 << COM1A1); /* output is OC1A */
	TCCR1B |= ((1 << CS12)); /* scale of 256 */

	/* page 142 - 16.4
	Here we set Waveform Generation to mode 14 */
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);

	/* The top is now on ICR1 */
	ICR1 = 62499; /* Same operation as before but with 1 Hz instead of 2 */

	OCR1A = 6250; /* 10% of ICR1 */
	/* page 145 - 16.11.9 When the timer reaches OCR1A it will trigger flag OCF1A,
	this flag will then trigger the LED */

	while (1) {
		;
	}
}
// page 142 ICR1
