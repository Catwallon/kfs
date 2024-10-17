#include "kernel.h"

void keyboard_handler()
{
	printf("d");
	// uint8_t scancode = inb(0x60);
	// static char scancode_to_char[] = {
	// 	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	// 	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	// 	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	// 	0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	// 	'*', 0, ' '
	// };
	// static int pressed[58];

	// if (scancode & 0x80)
	// 	pressed[scancode & 0x7F] = 0;
	// else if (!pressed[scancode])
	// {
	// 	pressed[scancode] = 1;
	// 	printf("%c", scancode_to_char[scancode]);
	// }
	outb(0x20, 0x20);
}
