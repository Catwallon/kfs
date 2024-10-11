#include "kernel.h"

struct idt_entry idt[256];

void pic_remap()
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0xFC);
	outb(0xA1, 0xFF);
}

void idt_install()
{
	struct idt_ptr idtp;

	idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
	idtp.base = (unsigned int)&idt;
	asm volatile("lidt (%0)" : : "r" (&idtp));
}

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
}

void irq_install()
{
	pic_remap();
	idt_install();
	idt_set_gate(32, (unsigned long)timer_handler, 0x08, 0x8E);
	idt_set_gate(33, (unsigned long)keyboard_handler, 0x08, 0x8E);
	asm volatile ("sti");
}