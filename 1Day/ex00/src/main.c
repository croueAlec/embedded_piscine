#include <avr/io.h>

typedef volatile uint16_t v16_t ;

#ifndef F_CPU
#define F_CPU 16000000
#endif

void	ft_delay(v16_t value)
{
	for (v16_t i = 0; i < value; i++) {
		for (v16_t i = 0; i < 1000; i++) {
			;
		}
	}
}

int	main(void)
{
	DDRB |= (1 << DDB0);

	while (1) {
		ft_delay(500);
		PORTB ^= (1 << PORTB0);
	}
}
