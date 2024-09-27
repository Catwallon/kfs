all:
	mkdir -p obj
	nasm -f elf32 -o obj/multiboot_header.o src/multiboot_header.asm
	ld -m elf_i386 -o kfs/multiboot_header obj/multiboot_header.o
	grub-mkrescue -o kfs.iso kfs
	qemu-system-i386 -cdrom kfs.iso -nographic
