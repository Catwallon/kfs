#include "kernel.h"

unsigned int g_char_pos = 0;

void kernel_main()
{
	gdt_install();
	idt_install();
	while (1)
	{
		// ...
	}
}