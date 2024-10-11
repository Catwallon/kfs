#pragma once

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80

#include <stdarg.h>
#include <stdint.h>
#include "irq.h"

extern unsigned int g_char_pos;

// io.c
void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

// handlers
void keyboard_handler();
void timer_handler();


void printf(char *format, ...);
