#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	DDRB |= (1 << DDB0);
	while (1) {
		if (!(PIND & (1 << PIND2))) {
			PORTB ^= (1 << PORTB0); /* Here we invert the current state of the pin 0 with an exclusive or*/

			while (!(PIND & (1 << PIND2))) { /* Once we changed the state we do an infinite loop until the button is released */
				;
			}
			_delay_ms(10000); /* Finally we wait to prevent bouncing */
		}
	}
}
