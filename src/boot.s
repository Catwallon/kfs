bits 32

; FLAGS
MBALIGN equ 1<<0
MEMINFO equ 1<<1
MEMVIDEO equ 1<<2

; MULTIBOOT
SIGNATURE equ 0x1BADB002
FLAGS equ (MBALIGN)
CHECKSUM equ -(SIGNATURE + FLAGS)

align 4
dd SIGNATURE
dd FLAGS
dd CHECKSUM 

section .bss
align 16
stack_bottom:
	resb 4096
stack_top:

extern kernel_main
section .text
global _start
_start:
	mov esp, stack_top
	call kernel_main

section .data
