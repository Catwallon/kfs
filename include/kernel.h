#pragma once

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80

#include "gdt.h"
#include "idt.h"
#include "printf.h"

// io.c
void outb(uint16_t port, unsigned char data);
unsigned char inb(uint16_t port);

// handlers
void keyboard_handler();
void timer_handler();
void generic_handler();

void exception_handler(void);
