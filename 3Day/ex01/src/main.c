#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void	rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	red &= 0b1;
	green &= 0b1;
	blue &= 0b1;

	PORTD = (red << PORTD5) | (green << PORTD6) | (blue << PORTD3);
	_delay_ms(1000);
}

int	main(void)
{
	DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6);

	while (1) {
		rgb(0xff,0,0);
		rgb(0,0xff,0);
		rgb(0,0,0xff);
		rgb(0xff,0xff,0);
		rgb(0,0xff,0xff);
		rgb(0xff,0,0xff);
		rgb(0xff,0xff,0xff);
	}
}
