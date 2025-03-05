#include <avr/io.h>

typedef volatile uint16_t v16_t ;

void	ft_delay(v16_t value)
{
	/* for loops have 4 instructions */
	for (v16_t i = 0; i < value; i++) { /* so we divide by 4 here */
		for (v16_t i = 0; i < 1000; i++) { /* and here as well, we also divide it by 1000 */
			;
		}
	}

	/* 16 000 000 / 4 = 4 000 000 */
	/* 4 000 000 / 4 = 1 000 000 */
	/* 1 000 000 / 1000 = 1000 */
	/* finally we divide by the value of our biggest loop which is 500 */
	/* 1000 / 500 = 2 We get 2 which is the number of operations we need to do per second */
}

int	main(void)
{
	DDRB |= (1 << DDB0);

	while (1) {
		ft_delay(500); /* 500ms is 0.5s */
		PORTB ^= (1 << PORTB0);
	}
}
