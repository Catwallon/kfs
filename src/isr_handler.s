global isr_handler_stub

extern common_stub

isr_handler_stub:
	pusha
	mov eax, [esp+32]
	push eax
	call common_stub
	add esp, 4
	popa
	iret