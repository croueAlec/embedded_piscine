#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	/* page 13 - 1.1.6 */
	DDRB |= (1 << DDB0);
	while (1) {
		if (!(PIND & (1 << PIND2))) { /* Here we check that PIND2 is in low mode (thus the !), in which case the switch is pressed. */
			PORTB |= (1 << PORTB0);
			_delay_ms(1000); /* Here we debounce to prevent the spam of state change when we interact with the button. */
		}
		else
		{
			PORTB &= ~(1 << PORTB0); /* Here we invert the state of PB0 while not changing the state of the others */
		}
	}
}
