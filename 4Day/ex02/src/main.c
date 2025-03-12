#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

volatile unsigned char count = 0;

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
	_delay_ms(20);
}

ISR(INT0_vect)
{
	if (count == 15)
		return;
	count++;
	update_leds(count);
	anti_bounce(PIND2);
}

ISR(PCINT2_vect)
{
	if (count == 0)
		return;
	count--;
	update_leds(count);
	anti_bounce(PIND4);
}

void	enable_switch_interrup() /* page 98 */
{
	EIMSK |= (1 << INT0); /* page 81 - 13.2.2 */
	PCMSK2 |= (1 << PCINT20); // This also works with PCINT18
}

void	enable_pin_interrupts()
{
	PCICR |= (1 << PCIE2); // But we also need to enable this for PCINT18
}

int	main(void)
{
	enable_pin_interrupts();
	enable_switch_interrup();

	sei();

	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);
	while (1) {
		;
	}
}
