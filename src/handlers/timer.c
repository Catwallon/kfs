#include "kernel.h"

void timer_handler()
{
	outb(0x20, 0x20);
}