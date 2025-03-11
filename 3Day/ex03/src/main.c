#include <avr/io.h>
#include <ctype.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "emb.h"

char	hex[8] = {0};
char	tmp[8] = {0};

char	*error = "Bad color format\n";
char	*success = "Color displayed\n";

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

void	uart_init()
{
	/* page 185 - 20.5 */
	UBRR0L = (uint8_t)((UBRRN) & 0xFF); /* Lower half of Baud Rate */
	UBRR0H = (uint8_t)((UBRRN) >> 8); /* Upper rate of Baud Rate */

	/* page 185 - 20.6  also page 201 - 20.11.3*/
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); /* Enable Receive and Transmit */

	/* page 182 - 20.3.2 */
	UCSR0A |= (1 << U2X0); /* Enabling double transfer speed, and divide by two baudrate */

	/* page 202 - 20.11.4 & 20-11*/
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); /* set transmission bit size */
}

void	uart_tx(char c)
{
	/* page 186 - 20.6.1 */
	while (!(UCSR0A & (1 << UDRE0))) /* Wait for empty buffer */
		;
	UDR0 = c; /* Set data in buffer */
}

uint8_t	convert_to_dec(char *str)
{
	uint8_t value = strtol(str, NULL, 16);
	str[0] = 0;
	return value;
}

void	hex_to_rgb(void)
{
	uint8_t b = convert_to_dec(&hex[5]);
	uint8_t g = convert_to_dec(&hex[3]);
	uint8_t r = convert_to_dec(&hex[1]);

	set_rgb(r, g, b);

	uart_tx('\n');
	for (uint8_t i = 0; success[i]; i++)
		uart_tx(success[i]);
	uart_tx('\r');
}

bool check_char(char c, uint8_t i) /* check color format */
{
	if (i == 0 && c != '#') {
		return 0;
	}
	if (i > 0 && i < 7) {
		if (!isxdigit(c))
			return 0;
	}
	if (i == 7 && c != '\r')
		return 0;

	return 1;
}

void	handle_error(void)
{
	memset(hex, 0, 8);

	uart_tx('\n');
	uart_tx('\r');
	for (uint8_t i = 0; error[i]; i++)
		uart_tx(error[i]);
	uart_tx('\r');

}

ISR(USART_RX_vect) /* Behavior of USART Receive */
{
	char	c = UDR0;
	uart_tx(c);

	uint8_t i = 0;
	for (; hex[i] && i < 8; i++) {
		;
	}
	if (!check_char(c, i)) {
		handle_error();
		return;
	}

	if (i == 7) {
		hex[i] = c;
		hex_to_rgb();
	} else {
		hex[i] = c;
	}
}

int	main(void)
{
	init_rgb();
	uart_init();

	UCSR0B |= (1 << RXCIE0); /* Enable receive interrupt */

	sei(); /* enable global interrupts */

	while (1) {
		;
	}
}
