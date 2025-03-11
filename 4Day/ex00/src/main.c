/* when pd2 pressed change pb0 state */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

ISR(PCINT2_vect)
{
	PORTB ^= (1 << PORTB0);
	/* add delay with state change with if in loop */
	/* maybe also look into interrupt on int0 */
}

void	enable_switch_interrup()
{
	PCMSK2 |= (1 << PCINT18);
}

void	enable_pin_interrupts()
{
	PCICR |= (1 << PCIE2);
}

int	main(void)
{
	DDRB |= (1 << DDD0);

	enable_pin_interrupts();
	enable_switch_interrup();

	sei();

	while (1) {
		;
	}
}
