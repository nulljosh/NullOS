/* NullOS Interrupt Descriptor Table
 *
 * Sets up the 256-entry IDT for handling CPU exceptions,
 * hardware interrupts (IRQs), and software interrupts (syscalls).
 *
 * See: docs/PHASES.md Phase 2.2
 */

/* TODO: Implement IDT
 *
 * IDT entry structure (8 bytes):
 *   uint16_t offset_low;    // Handler address bits 0-15
 *   uint16_t selector;      // Code segment selector (0x08)
 *   uint8_t  zero;          // Always 0
 *   uint8_t  type_attr;     // Type and attributes (0x8E for interrupt gate)
 *   uint16_t offset_high;   // Handler address bits 16-31
 *
 * Functions:
 *   idt_init()               - Create and load the IDT
 *   idt_set_gate(n, handler) - Set handler for interrupt n
 */
