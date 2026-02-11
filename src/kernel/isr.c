/* NullOS Interrupt Service Routines
 *
 * Handles CPU exceptions (interrupts 0-31).
 * ISR stubs are in assembly; this file contains the C handlers.
 *
 * See: docs/PHASES.md Phase 2.3
 */

#include <kernel/isr.h>
#include <kernel/vga.h>
#include <lib/string.h>
#include <stdint.h>

/* CPU exception names */
static const char *exception_names[] = {
    "Division by zero",
    "Debug exception",
    "NMI interrupt",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Device not available (no FPU)",
    "Double fault",
    "Coprocessor segment overrun",
    "Invalid TSS",
    "Segment not present",
    "Stack segment fault",
    "General protection fault",
    "Page fault",
    "Reserved",
    "Floating point exception",
    "Alignment check",
    "Machine check",
    "SIMD floating point exception",
};

/* Register structure passed by ISR stubs */
typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

/* Default exception handler */
static void isr_handler_default(registers_t *regs) {
    const char *name = "Unknown";
    
    if (regs->int_no < 20) {
        name = exception_names[regs->int_no];
    }
    
    vga_puts("\n");
    vga_set_color(7, 1);  /* White on blue */
    vga_puts("===== CPU EXCEPTION =====\n");
    vga_puts("Exception: ");
    vga_puts(name);
    vga_puts("\n");
    
    vga_puts("Int #: ");
    vga_putchar('0' + (regs->int_no / 10));
    vga_putchar('0' + (regs->int_no % 10));
    vga_puts("\n");
    
    if (regs->int_no == 14) {
        /* Page fault - print address */
        vga_puts("Page fault address: 0x");
        uint32_t cr2;
        asm volatile("mov %%cr2, %0" : "=r"(cr2));
        
        for (int i = 28; i >= 0; i -= 4) {
            uint32_t nibble = (cr2 >> i) & 0xF;
            vga_putchar(nibble < 10 ? '0' + nibble : 'A' + nibble - 10);
        }
        vga_puts("\n");
    }
    
    vga_puts("Error code: 0x");
    for (int i = 28; i >= 0; i -= 4) {
        uint32_t nibble = (regs->err_code >> i) & 0xF;
        vga_putchar(nibble < 10 ? '0' + nibble : 'A' + nibble - 10);
    }
    vga_puts("\n");
    
    vga_puts("EIP: 0x");
    for (int i = 28; i >= 0; i -= 4) {
        uint32_t nibble = (regs->eip >> i) & 0xF;
        vga_putchar(nibble < 10 ? '0' + nibble : 'A' + nibble - 10);
    }
    vga_puts("\n");
    
    vga_puts("========================\n");
    vga_set_color(7, 0);  /* Reset to white on black */
    
    /* Halt */
    while (1) {
        asm volatile("hlt");
    }
}

/* Initialize ISR handlers */
void isr_init(void) {
    /* Currently using stub handlers defined in assembly
     * More sophisticated handler dispatch can be added here
     */
}

/* ISR wrapper - called from assembly stubs
 * The assembly stub will:
 * 1. Push all registers
 * 2. Call isr_common_handler with the register struct
 * 3. Pop all registers
 * 4. IRET
 */
void isr_common_handler(uint32_t int_no, uint32_t err_code) {
    /* Temporary handler - will be enhanced */
    registers_t regs;
    regs.int_no = int_no;
    regs.err_code = err_code;
    
    isr_handler_default(&regs);
}

/* ISR stubs - these are placeholders
 * In a real OS, these would be generated programmatically
 * or written in assembly with proper register save/restore
 */

/* Macro to create ISR stubs (simplified) */
#define ISR_STUB(n) \
    __asm__( \
        ".global isr"#n"\n\t" \
        "isr"#n":\n\t" \
        "    cli\n\t" \
        "    push $0\n\t" \
        "    push $"#n"\n\t" \
        "    jmp isr_common\n" \
    )

/* Generate ISR 0-19 stubs */
ISR_STUB(0);
ISR_STUB(1);
ISR_STUB(2);
ISR_STUB(3);
ISR_STUB(4);
ISR_STUB(5);
ISR_STUB(6);
ISR_STUB(7);
ISR_STUB(8);
ISR_STUB(9);
ISR_STUB(10);
ISR_STUB(11);
ISR_STUB(12);
ISR_STUB(13);
ISR_STUB(14);
ISR_STUB(15);
ISR_STUB(16);
ISR_STUB(17);
ISR_STUB(18);
ISR_STUB(19);

/* Common ISR entry point */
__asm__(
    ".global isr_common\n\t"
    "isr_common:\n\t"
    "    pusha\n\t"
    "    push %ds\n\t"
    "    mov $0x10, %ax\n\t"
    "    mov %ax, %ds\n\t"
    "    mov %ax, %es\n\t"
    "    mov %ax, %fs\n\t"
    "    mov %ax, %gs\n\t"
    "    pop %eax\n\t"
    "    push %eax\n\t"
    "    pop %edx\n\t"
    "    pop %ecx\n\t"
    "    call isr_common_handler\n\t"
    "    push %eax\n\t"
    "    pop %edx\n\t"
    "    mov %edx, %ds\n\t"
    "    mov %edx, %es\n\t"
    "    mov %edx, %fs\n\t"
    "    mov %edx, %gs\n\t"
    "    popa\n\t"
    "    add $8, %esp\n\t"
    "    iret\n"
);
