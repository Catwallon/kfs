#include "kernel.h"

void write_char(char c)
{
	volatile char* framebuffer = (volatile char*) VGA_ADDRESS;

	framebuffer[g_char_pos * 2] = c;
	framebuffer[g_char_pos * 2 + 1] = 0x0F;
	g_char_pos++;
}

void write_str(char *str)
{
	for (unsigned int i = 0; str[i]; i++)
		write_char(str[i]);
}

void write_nbr(long nb)
{
	if (nb < 0)
	{
		write_char('-');
		nb *= -1;
	}
	if (nb > 9)
		write_nbr(nb / 10);
	write_char(nb % 10 + '0');
}

void printf(char *format, ...)
{
	va_list args;

	va_start(args, format);
	for (unsigned int i = 0; format[i]; i++)
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c')
				write_char(va_arg(args, int));
			else if (format[i] == 's')
				write_str(va_arg(args, char *));
			else if (format[i] == 'd')
				write_nbr(va_arg(args, int));
		}
		else
			write_char(format[i]);
	}
	va_end(args);
}