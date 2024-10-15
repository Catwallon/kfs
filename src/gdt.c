#include "gdt.h"

static struct gdt_ptr gdtp;

__attribute__((aligned(0x10))) 
static struct gdt_entry gdt[3];

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = (limit >> 16) & 0x0F;
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void gdt_flush(uint32_t gdtp)
{
	asm volatile
	(
		"lgdt (%0)\n\t"
		"mov $0x10, %%ax\n\t"
		"mov %%ax, %%ds\n\t"
		"mov %%ax, %%es\n\t"
		"mov %%ax, %%fs\n\t"
		"mov %%ax, %%gs\n\t"
		"mov %%ax, %%ss\n\t"
		"jmp $0x08, $.flush\n"
		".flush:\n\t"
		:
		: "r"(gdtp)
		: "ax"
	);
}

void gdt_install()
{
	gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gdtp.base = (uint32_t)&gdt;
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_flush((uint32_t)&gdtp);
}
