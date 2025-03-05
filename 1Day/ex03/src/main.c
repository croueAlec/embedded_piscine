#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define MAX_MULT 10
#define MIN_MULT 1
#define TEN_PERC 6250

void	anti_bounce(volatile uint8_t pin)
{
	while (!(PIND & (1 << pin))) {
		;
	}
	_delay_ms(20);
}

void	is_pressed(volatile uint8_t pin, uint8_t *multiplicator)
{
	if (!(PIND & (1 << pin))) {
		if (pin == PIND2 && ((*multiplicator) < MAX_MULT)) {
			(*multiplicator)++;
		} else if (pin == PIND4 && ((*multiplicator) > MIN_MULT)) {
			(*multiplicator)--;
		} else {
			return;
		}
		OCR1A = (*multiplicator) * TEN_PERC;
		anti_bounce(pin);
	}
}

int	main(void)
{
	DDRB |= (1 << PORTB1);

	TCCR1A |= (1 << COM1A1); /* output is OC1A */
	TCCR1B |= ((1 << CS12)); /* scale of 256 */

	TCCR1A |= (1 << WGM11); /* Mode 14 */
	TCCR1B |= (1 << WGM13) | (1 << WGM12);

	ICR1 = 62499; /* TOP */

	OCR1A = TEN_PERC;

	uint8_t	multiplicator = MIN_MULT;

	while (1) {
		is_pressed(PIND2, &multiplicator);
		is_pressed(PIND4, &multiplicator);
	}
}
