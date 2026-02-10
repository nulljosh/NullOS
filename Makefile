# NullOS Makefile
# Builds a bootable x86 floppy image from assembly bootloader + C kernel

# --- Toolchain ---
ASM       = nasm
CC        = i686-elf-gcc
LD        = i686-elf-ld
OBJCOPY   = i686-elf-objcopy
QEMU      = qemu-system-i386

# --- Directories ---
SRC_BOOT  = src/boot
SRC_KERN  = src/kernel
SRC_DRV   = src/drivers
SRC_LIB   = src/lib
INC       = include
BUILD     = build
BUILD_BOOT = $(BUILD)/boot
BUILD_KERN = $(BUILD)/kernel
BUILD_DRV  = $(BUILD)/drivers
BUILD_LIB  = $(BUILD)/lib

# --- Flags ---
ASMFLAGS  = -f bin
ASMFLAGS_ELF = -f elf32
CFLAGS    = -m32 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector \
            -nostdlib -nostdinc -Wall -Wextra -Werror -O2 -I$(INC)
LDFLAGS   = -T linker.ld -nostdlib

# --- Output ---
IMAGE     = $(BUILD)/nullos.img
BOOT_BIN  = $(BUILD_BOOT)/boot.bin
KERNEL_BIN = $(BUILD_KERN)/kernel.bin
KERNEL_ELF = $(BUILD_KERN)/kernel.elf

# --- Source files ---
# Boot assembly files (compiled to flat binary)
BOOT_SRCS = $(SRC_BOOT)/stage1.asm

# Kernel assembly files (compiled to ELF objects)
KERN_ASM_SRCS = $(SRC_BOOT)/stage2.asm $(SRC_BOOT)/gdt.asm $(SRC_BOOT)/a20.asm
KERN_ASM_OBJS = $(patsubst $(SRC_BOOT)/%.asm,$(BUILD_BOOT)/%.o,$(KERN_ASM_SRCS))

# Kernel C files
KERN_C_SRCS = $(wildcard $(SRC_KERN)/*.c)
KERN_C_OBJS = $(patsubst $(SRC_KERN)/%.c,$(BUILD_KERN)/%.o,$(KERN_C_SRCS))

# Driver C files
DRV_C_SRCS  = $(wildcard $(SRC_DRV)/*.c)
DRV_C_OBJS  = $(patsubst $(SRC_DRV)/%.c,$(BUILD_DRV)/%.o,$(DRV_C_SRCS))

# Lib C files
LIB_C_SRCS  = $(wildcard $(SRC_LIB)/*.c)
LIB_C_OBJS  = $(patsubst $(SRC_LIB)/%.c,$(BUILD_LIB)/%.o,$(LIB_C_SRCS))

# All kernel objects (asm + C)
ALL_OBJS    = $(KERN_ASM_OBJS) $(KERN_C_OBJS) $(DRV_C_OBJS) $(LIB_C_OBJS)

# --- QEMU flags ---
QEMU_FLAGS = -fda $(IMAGE) -boot a -serial stdio -m 32M
QEMU_DEBUG = $(QEMU_FLAGS) -s -S

# ===========================================================================
# Targets
# ===========================================================================

.PHONY: all run debug clean boot kernel dirs

all: $(IMAGE)

# --- Create build directories ---
dirs:
	@mkdir -p $(BUILD_BOOT) $(BUILD_KERN) $(BUILD_DRV) $(BUILD_LIB)

# --- Full disk image: bootloader (512 bytes) + kernel ---
$(IMAGE): dirs $(BOOT_BIN) $(KERNEL_BIN)
	@echo "  IMG   $@"
	@dd if=/dev/zero of=$@ bs=512 count=2880 status=none
	@dd if=$(BOOT_BIN) of=$@ bs=512 count=1 conv=notrunc status=none
	@dd if=$(KERNEL_BIN) of=$@ bs=512 seek=1 conv=notrunc status=none
	@echo ""
	@echo "  NullOS image built: $@ (1.44 MB floppy)"
	@echo "  Run with: make run"

# --- Stage 1 bootloader (flat binary, exactly 512 bytes) ---
$(BOOT_BIN): $(SRC_BOOT)/stage1.asm | dirs
	@echo "  ASM   $<"
	@$(ASM) $(ASMFLAGS) $< -o $@

# --- Kernel binary (ELF -> flat binary) ---
$(KERNEL_BIN): $(KERNEL_ELF)
	@echo "  BIN   $@"
	@$(OBJCOPY) -O binary $< $@

# --- Kernel ELF (link all objects) ---
$(KERNEL_ELF): $(ALL_OBJS) linker.ld
	@echo "  LD    $@"
	@$(LD) $(LDFLAGS) -o $@ $(ALL_OBJS)

# --- Compile kernel assembly to ELF objects ---
$(BUILD_BOOT)/%.o: $(SRC_BOOT)/%.asm | dirs
	@echo "  ASM   $<"
	@$(ASM) $(ASMFLAGS_ELF) $< -o $@

# --- Compile kernel C files ---
$(BUILD_KERN)/%.o: $(SRC_KERN)/%.c | dirs
	@echo "  CC    $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# --- Compile driver C files ---
$(BUILD_DRV)/%.o: $(SRC_DRV)/%.c | dirs
	@echo "  CC    $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# --- Compile lib C files ---
$(BUILD_LIB)/%.o: $(SRC_LIB)/%.c | dirs
	@echo "  CC    $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# --- Run in QEMU ---
run: $(IMAGE)
	@echo "  QEMU  $(IMAGE)"
	@$(QEMU) $(QEMU_FLAGS)

# --- Run with GDB stub ---
debug: $(IMAGE)
	@echo "  QEMU  $(IMAGE) (waiting for GDB on :1234)"
	@echo "  Connect with: gdb $(KERNEL_ELF) -ex 'target remote :1234'"
	@$(QEMU) $(QEMU_DEBUG)

# --- Build bootloader only (for Phase 1 testing) ---
boot: dirs $(BOOT_BIN)
	@echo "  Boot sector built: $(BOOT_BIN)"
	@echo "  Test with: $(QEMU) -fda $(BOOT_BIN)"

# --- Build kernel only ---
kernel: dirs $(KERNEL_BIN) $(KERNEL_ELF)
	@echo "  Kernel built: $(KERNEL_BIN)"

# --- Clean ---
clean:
	@echo "  CLEAN build/"
	@rm -rf $(BUILD)
