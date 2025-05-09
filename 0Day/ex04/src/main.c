#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void	update_leds(unsigned char count)
{
	PORTB = 0;
	if (count & 0b1000)	/* If the 4th bit of count is one we toggle the PORTB4 LED */
	{
		PORTB |= (1 << PORTB4);
		count ^= 0b1000;	/* Then we set the 4th bit of count to 0 */
	}
	PORTB |= count;	/* And we apply the rest of count to match their LEDs */
}

void	anti_bounce(volatile uint8_t pin)
{
	while (!(PIND & (1 << pin))) {
		;
	}
	_delay_ms(1000);
}

int	main(void)
{
	unsigned char count = 0;

	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);
	while (1) {
		if (!(PIND & (1 << PIND2)) && count < 15) {
			count++;
			update_leds(count);
			anti_bounce(PIND2);
		} else if (!(PIND & (1 << PIND4)) && count > 0) {
			count--;
			update_leds(count);
			anti_bounce(PIND4);
		}
	}
}
