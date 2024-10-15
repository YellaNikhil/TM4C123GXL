#ifndef _UART_H_
#define _UART_H_


#include "gpio_registers.h"



/* Flag Regsiter check*/
#define	TRANSMIT_FIFO_EMPTY 0x80
#define RECEIVE_FIFO_FULL 0x40
#define TRANSMIT_FIFO_FULL 0x20
#define RECEIVE_FIFO_EMPTY 0x10
#define UART_BUSY 0x08
#define CLEAR_TO_SEND 0x00




typedef struct{
	UART0_Type *uart;
	gpio_info *tx;
	gpio_info *rx;
	uint32_t baud_rate_integer_value;
	uint32_t baud_rate_decimal_value;
	uint32_t clock_source;
	uint32_t data_length;
	uint32_t parity_bit;
	uint32_t interrupt_enable;
	uint8_t *data;
}uart_handler;

void uart_init(uart_handler*);
void uart_transmit_data(uart_handler *, const char *);
char* uart_receive_data(uart_handler *);


#endif

