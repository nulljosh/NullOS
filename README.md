# NullOS

A custom operating system built from scratch.

## Project Goals

- Understand low-level system architecture
- Learn about bootloaders, kernel development, and hardware interaction
- Build a minimal but functional OS

## Development Phases

### Phase 1: Bootloader
- [ ] Create a simple bootloader (GRUB or custom)
- [ ] Boot into 16-bit real mode
- [ ] Switch to 32-bit protected mode

### Phase 2: Kernel Basics
- [ ] Set up GDT (Global Descriptor Table)
- [ ] Implement basic VGA text mode output
- [ ] Set up IDT (Interrupt Descriptor Table)
- [ ] Keyboard input handler

### Phase 3: Memory Management
- [ ] Physical memory manager
- [ ] Virtual memory (paging)
- [ ] Heap allocator

### Phase 4: Process Management
- [ ] Task switching
- [ ] Scheduler
- [ ] Multitasking support

### Phase 5: File System
- [ ] VFS (Virtual File System) layer
- [ ] Simple file system implementation

## Tech Stack

- **Language**: C, Assembly (x86/x86_64)
- **Build Tools**: GCC, NASM, Make
- **Testing**: QEMU, Bochs
- **Target Architecture**: x86_64

## Resources

- [OSDev Wiki](https://wiki.osdev.org/)
- [James Molloy's Kernel Tutorial](http://www.jamesmolloy.co.uk/tutorial_html/)
- [Writing a Simple Operating System from Scratch](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
- [Linux From Scratch](https://www.linuxfromscratch.org/)

## Setup

```bash
# Install cross-compiler toolchain
# Install QEMU for testing
# Build the kernel
make
# Run in QEMU
make run
```

## License

MIT
