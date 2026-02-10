/* NullOS Kernel Entry Point
 *
 * Called from Stage 2 bootloader after switching to protected mode.
 * Initializes all kernel subsystems and launches the shell.
 *
 * See: docs/PHASES.md Phase 2
 */

#include <kernel/vga.h>
#include <lib/string.h>

/* Kernel entry point -- called from assembly at 0x100000 */
void kmain(void) {
    /* Initialize VGA driver for text output */
    vga_init();
    vga_puts("=== NullOS Kernel Boot ===\n");
    vga_puts("Kernel entry point reached at 0x100000\n");
    vga_puts("VGA text mode initialized (80x25)\n");
    vga_puts("\n");
    
    /* TODO: Phase 2 initialization
     * idt_init();
     * isr_init();
     * irq_init();
     * timer_init(100);       // 100 Hz
     * keyboard_init();
     * asm volatile("sti");   // Enable interrupts
     */
    
    vga_puts("Phase 2 (Interrupts): TODO\n");
    
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
    vga_puts("Boot sequence complete. System ready.\n");
    
    /* Halt the system */
    for (;;) {
        asm volatile("hlt");
    }
}
