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

void write_int(int32_t nb)
{
	if (nb < 0)
	{
		write_char('-');
		nb *= -1;
	}
	if (nb >= 10)
		write_int(nb / 10);
	write_char(nb % 10 + '0');
}

void write_uint(uint32_t nb)
{
	if (nb >= 10)
		write_uint(nb / 10);
	write_char(nb % 10 + '0');
}

void write_int_hexa(int32_t nb)
{
	if (nb >= 16)
		write_int_hexa(nb / 16);
	write_char("0123456789abcdef"[nb % 16]);
}

void write_uint_hexa(uint32_t nb)
{
	if (nb >= 16)
		write_uint_hexa(nb / 16);
	write_char("0123456789abcdef"[nb % 16]);
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
				write_int(va_arg(args, int32_t));
			else if (format[i] == 'u')
				write_uint(va_arg(args, uint32_t));
			else if (format[i] == 'x')
			{
				write_str("0x");
				write_uint_hexa((uint32_t)va_arg(args, void *));
			}
		}
		else
			write_char(format[i]);
	}
	va_end(args);
}