NAME = kfs.iso

ASM = nasm
ASMFLAGS = -f elf32
CC = gcc
CFLAGS = -m32 -ffreestanding -fno-builtin \
			-fno-exceptions -fno-stack-protector \
			-nostdlib -nodefaultlibs \
			-Wall -Wextra -Werror

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj

ASM_SRC = $(shell find $(SRC_DIR) -name '*.s')
C_SRC = $(shell find $(SRC_DIR) -name '*.c')
ASM_OBJ = $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(ASM_SRC))
C_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRC))

GRUB_MODULES = multiboot normal
GRUB_RM = boot/grub/x86_64-efi boot/grub/i386-efi System mach_kernel efi efi.img

all: $(NAME)

run: $(NAME)
	qemu-system-i386 -enable-kvm -m 512M -cdrom $^

$(NAME): $(ASM_OBJ) $(C_OBJ)
	ld -m elf_i386 -T linker.ld -o kfs/kernel $^
	grub-mkrescue --themes="" --install-modules="$(GRUB_MODULES)" -o $@ kfs -- -rm_r $(GRUB_RM)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(ASM) $(ASMFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
