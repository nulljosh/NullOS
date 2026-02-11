/* NullOS Kernel Entry Point
 *
 * Called from Stage 2 bootloader after switching to protected mode.
 * Initializes all kernel subsystems and launches the shell.
 *
 * See: docs/PHASES.md Phase 2
 */

#include <kernel/vga.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/irq.h>
#include <lib/string.h>

/* Kernel entry point -- called from assembly at 0x100000 */
void kmain(void) {
    /* Initialize VGA driver for text output */
    vga_init();
    vga_puts("=== NullOS Kernel Boot ===\n");
    vga_puts("Kernel entry point reached at 0x100000\n");
    vga_puts("VGA text mode initialized (80x25)\n");
    vga_puts("\n");
    
    /* Phase 2 initialization - Interrupts */
    vga_puts("Initializing interrupts...\n");
    idt_init();
    vga_puts("  IDT loaded\n");
    
    isr_init();
    vga_puts("  ISRs initialized\n");
    
    irq_init();
    vga_puts("  IRQs initialized and remapped\n");
    
    /* Enable interrupts */
    asm volatile("sti");
    vga_puts("  Interrupts enabled\n");
    vga_puts("\n");
    
    /* TODO: Phase 2 (continued) initialization
     * timer_init(100);       // 100 Hz (IRQ0)
     * keyboard_init();       // PS/2 keyboard (IRQ1)
     * shell_init();          // Command shell
     */
    
    vga_puts("Phase 2 (Interrupts): PARTIAL\n");
    vga_puts("Phase 2 (Timer/Keyboard): TODO\n");
    
    /* TODO: Phase 3 initialization
     * pmm_init(memory_map);
     * paging_init();
     * heap_init(HEAP_START, HEAP_SIZE);
     */
    
    vga_puts("Phase 3 (Memory Management): TODO\n");
    
    /* TODO: Phase 4 initialization
     * scheduler_init();
     */
    
    vga_puts("Phase 4 (Multitasking): TODO\n");
    vga_puts("\n");
    vga_puts("Boot sequence complete. Kernel ready.\n");
    vga_puts("Waiting for interrupts...\n");
    
    /* Halt the system - wait for interrupts */
    for (;;) {
        asm volatile("hlt");
    }
}
