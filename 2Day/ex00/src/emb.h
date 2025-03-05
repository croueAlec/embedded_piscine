#pragma once

#ifndef F_CPU
#define F_CPU 16000000
#endif

#ifndef UART_BAUDRATE
#define UART_BAUDRATE 115200
#endif

#define UBRRN F_CPU / (8 * UART_BAUDRATE) - 1
