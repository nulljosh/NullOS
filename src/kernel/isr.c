/* NullOS Interrupt Service Routines
 *
 * Handles CPU exceptions (interrupts 0-31).
 * ISR stubs are in assembly; this file contains the C handlers.
 *
 * See: docs/PHASES.md Phase 2.3
 */

/* TODO: Implement ISR handlers
 *
 * Register structure passed to C handlers:
 *   typedef struct {
 *       uint32_t ds;
 *       uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  // pusha
 *       uint32_t int_no, err_code;
 *       uint32_t eip, cs, eflags, useresp, ss;             // pushed by CPU
 *   } registers_t;
 *
 * Functions:
 *   isr_init()                    - Register all exception handlers
 *   isr_handler(registers_t *r)   - Dispatch to specific handler
 */
