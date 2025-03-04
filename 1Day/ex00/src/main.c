#include <avr/io.h>

typedef volatile uint16_t v16_t ;

void	ft_delay(uint16_t delay)
{
	for (v16_t i = 0; i < delay; i++) {
		for (v16_t j = 0; j < (v16_t)1600; j++) {
			;
		}
	}
}

int	main(void)
{
	DDRB |= (1 << DDB1);

	while (1) {
		ft_delay((v16_t)500);
		PORTB ^= (1 << PORTB1);
	}
}
