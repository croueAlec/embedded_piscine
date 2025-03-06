#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_rgb()
{
	DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6); /* out RGB */

	TCCR0A |= (1 << COM0A1) | (1 << COM0B1); /* page 113 - 15-3 */
	TCCR0A |= (1 << WGM01) | (1 << WGM00); /* page 115 - 15-8 mode 3 top 255 */
	TCCR0B |= (1 << CS00); /* clock source */

	TCCR2A |= (1 << COM2B1); /* page 163 */
	TCCR2A |= (1 << WGM21) | (1 << WGM20); /* page 164 - 18-8 mode 3 top 255 */
	TCCR2B |= (1 << CS20); /* clock source */

	OCR0A = 0;
	OCR0B = 0;
	OCR2B = 0;
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	OCR0B = r;
	OCR0A = g;
	OCR2B = b;
}

void wheel(uint8_t pos) {
	pos = 255 - pos;
	if (pos < 85) {
		set_rgb(255 - pos * 3, 0, pos * 3);
	} else if (pos < 170) {
		pos = pos - 85;
		set_rgb(0, pos * 3, 255 - pos * 3);
	} else {
		pos = pos - 170;
		set_rgb(pos * 3, 255 - pos * 3, 0);
	}
}

int	main(void)
{
	init_rgb();

	while (1) {
		for (uint8_t i = 0; i < 255; i++) {
			wheel(i);
			_delay_ms(20);
		}
	}
}
