#include "kernel.h"

static struct idt_ptr idtp;

__attribute__((aligned(0x10))) 
static struct idt_entry idt[256];

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
	outb(0x21, 0x00);
	outb(0xA1, 0x00);
}

void idt_set_gate(unsigned char num, uint32_t base, uint16_t sel, unsigned char flags)
{
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;
	idt[num].kernel_cs = sel;
	idt[num].reserved = 0;
	idt[num].flags = flags;
}

void idt_install()
{
	pic_remap();
	idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
	idtp.base = (uint32_t)&idt;
	asm volatile("lidt %0" : : "m" (idtp));
	for (int i = 0; i < 256; i++)
	{
		if (i == 32)
			idt_set_gate(i, (uint32_t)timer_handler, 0x08, 0x8E);
		else if (i == 33)
			idt_set_gate(i, (uint32_t)keyboard_handler, 0x08, 0x8E);
		else
			idt_set_gate(i, (uint32_t)generic_handler, 0x08, 0x8E);	
	}
	asm volatile ("sti");
}
