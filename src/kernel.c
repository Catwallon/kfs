#include "kernel.h"

unsigned int g_char_pos = 0;

void kernel_main()
{
	irq_install();
	while (1)
	{
		// ...
	}
}