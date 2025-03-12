/* when pd2 pressed change pb0 state */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

volatile bool state = 0;

// ISR(PCINT2_vect)
ISR(INT0_vect)
{
	if (state == 0)
		state = 1;
}

void	enable_switch_interrup() /* page 98 */
{
	/* Here we enable interrupts on INT0 */
	EIMSK |= (1 << INT0); /* page 81 - 13.2.2 */
	// PCMSK2 |= (1 << PCINT18); // This also works with PCINT18
}

// void	enable_pin_interrupts()
// {
// 	PCICR |= (1 << PCIE2); // But we also need to enable this for PCINT18
// }

int	main(void)
{
	DDRB |= (1 << DDD0);

	// enable_pin_interrupts();
	enable_switch_interrup();

	sei();

	while (1) {
		if (state == 1) {
			PORTB ^= (1 << PORTB0);
			_delay_ms(20);
			state = 0;
		}
	}
}
