#include "kernel.h"

void outb(uint16_t port, unsigned char data)
{
	asm volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

unsigned char inb(uint16_t port)
{
	unsigned char ret;

	asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return (ret);
}