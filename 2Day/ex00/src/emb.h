#pragma once

#ifndef F_CPU
#define F_CPU 16000000
#endif

#ifndef UART_BAUDRATE
#define UART_BAUDRATE 115200
#endif

/* page 182 - 20-1 Baud Rate for double speed mode (page 182 - 20.3.2) */
#define UBRRN ((F_CPU / (8 * UART_BAUDRATE)) - 1)
