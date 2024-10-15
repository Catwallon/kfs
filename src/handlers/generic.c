#include "kernel.h"

void generic_handler()
{
	outb(0x20, 0x20);
}