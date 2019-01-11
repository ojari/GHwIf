// windows implementation of drivers hal layer (see drivers repository)
//
#include "hw.h"
#include "hal.h"
#include <iostream>

void delay_us(uint16_t time)
{
	std::cout << "delay_us: " << time << std::endl;
}

void io_init()
{
	std::cout << "io_init" << std::endl;
}

void io_pin_init(pin_t pin, uint8_t mode)
{
	std::cout << "io_pin_init: " << pin << ", " << mode << std::endl;
}

void io_mode(pin_t, uint8_t mode)
{
	std::cout << "io_mode: " << mode << std::endl;
}

void io_set(pin_t pin)
{
	std::cout << "io_set: " << pin << std::endl;
}

void io_clear(pin_t pin)
{
	std::cout << "io_clear: " << pin << std::endl;
}

uint8_t io_read(pin_t pin)
{
	std::cout << "io_read: " << pin << std::endl;
	return 0;
}

void uart_init(uint8_t port)
{
	std::cout << "uart_init: " << port << std::endl;
}

void uart_print(uint8_t port, buffer_t *buf)  // async send command
{
	std::cout << "uart_print: " << port << ", " << buf << std::endl;
}

void uart_sync(uint8_t port, buffer_t *buf)
{
	std::cout << "uart_sync: " << port << ", " << buf << std::endl;
}

void uart_send(uint8_t port, char ch)    // old version use uart_print
{
	std::cout << "uart_send: " << port << ", " << ch << std::endl;
}

void uart_sends(uint8_t port, char *buf)
{
	std::cout << "uart_sends: " << port << ", " << buf << std::endl;
}

void uart_send_nl(uint8_t port)
{
	std::cout << "uart_send_nl: " << port << std::endl;
}

void timer2_init()
{
	std::cout << "timer2_init" << std::endl;
}

void spi_init(uint8_t port)
{
	std::cout << "spi_init: " << port << std::endl;
}

uint16_t spi_write(uint8_t port, uint16_t data)
{
	std::cout << "spi_write: " << port << ", " << data << std::endl;
	return 0;
}