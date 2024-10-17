#include "kernel.h"

void timer_handler()
{
	printf("d");
	outb(0x20, 0x20);
}