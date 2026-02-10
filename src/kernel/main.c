/* NullOS Kernel Entry Point
 *
 * Called from Stage 2 bootloader after switching to protected mode.
 * Initializes all kernel subsystems and launches the shell.
 *
 * See: docs/PHASES.md Phase 2
 */

/* TODO: Include kernel headers
 * #include <kernel/vga.h>
 * #include <kernel/idt.h>
 * #include <kernel/isr.h>
 * #include <kernel/irq.h>
 * #include <kernel/timer.h>
 * #include <kernel/keyboard.h>
 * #include <kernel/shell.h>
 * #include <kernel/memory.h>
 * #include <kernel/paging.h>
 * #include <kernel/heap.h>
 */

/* Kernel entry point -- called from assembly */
void kmain(void)
{
    /* TODO: Phase 2 initialization
     * vga_init();
     * vga_puts("NullOS v0.1\n");
     * idt_init();
     * isr_init();
     * irq_init();
     * timer_init(100);       // 100 Hz
     * keyboard_init();
     * asm volatile("sti");   // Enable interrupts
     */

    /* TODO: Phase 3 initialization
     * pmm_init(memory_map);
     * paging_init();
     * heap_init(HEAP_START, HEAP_SIZE);
     */

    /* TODO: Phase 4 initialization
     * scheduler_init();
     */

    /* TODO: Launch shell
     * shell_run();
     */

    /* Halt -- should never reach here */
    for (;;) {
        asm volatile("hlt");
    }
}
