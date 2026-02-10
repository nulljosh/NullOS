/* NullOS Hardware Interrupt Handlers
 *
 * Remaps the 8259 PIC and handles IRQs 0-15 (interrupts 32-47).
 *
 * See: docs/PHASES.md Phase 2.4
 */

/* TODO: Implement IRQ handling
 *
 * PIC remapping:
 *   Master PIC (0x20/0x21): IRQ 0-7 -> INT 32-39
 *   Slave PIC  (0xA0/0xA1): IRQ 8-15 -> INT 40-47
 *
 * Functions:
 *   irq_init()                      - Remap PIC, register IRQ handlers
 *   irq_handler(registers_t *r)     - Dispatch + send EOI
 *   irq_install_handler(n, handler) - Register handler for IRQ n
 */
