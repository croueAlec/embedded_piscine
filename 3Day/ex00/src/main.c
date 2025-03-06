#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void	next_color(void)
{
	if (PORTD & (1 << PORTD5)){
		PORTD = (1 << PORTD6);
	} else if (PORTD & (1 << PORTD6)) {
		PORTD = (1 << PORTD3);
	} else if (PORTD & (1 << PORTD3)) {
		PORTD = (1 << PORTD5);
	} else {
		PORTD = (1 << PIND5);
	}
}

int	main(void)
{
	DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6);

	while (1) {
		next_color();
		_delay_ms(1000);
	}
}
