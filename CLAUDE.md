# NullOS - Development Plan

Building a custom operating system from scratch to understand low-level system architecture.

## What We're Building
1. Bootloader (GRUB or custom) - boot into 16-bit, switch to 32-bit protected mode
2. Basic kernel - GDT, VGA text output, IDT, keyboard input
3. Memory management - physical memory manager, virtual memory (paging), heap allocator
4. Process management - task switching, scheduler, multitasking
5. File system - VFS layer and simple file system implementation

## Tech: C, x86_64 Assembly, QEMU for testing
