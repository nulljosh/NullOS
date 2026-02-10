/* NullOS PS/2 Keyboard Driver
 *
 * Handles IRQ 1 (interrupt 33). Reads scancodes from port 0x60,
 * converts to ASCII, and stores in a ring buffer.
 *
 * See: docs/PHASES.md Phase 2.6
 */

/* TODO: Implement keyboard driver
 *
 * Scan code set 1 (US QWERTY):
 *   Build a 128-entry lookup table mapping scancodes to ASCII.
 *   Handle shift state for uppercase and symbols.
 *   Key press = make code (bit 7 clear), release = break code (bit 7 set).
 *
 * Ring buffer:
 *   #define KB_BUFFER_SIZE 256
 *   static char kb_buffer[KB_BUFFER_SIZE];
 *   static int kb_read_idx, kb_write_idx;
 *
 * Functions:
 *   keyboard_init()    - Install IRQ 1 handler
 *   keyboard_handler() - Read scancode, convert, buffer
 *   keyboard_getchar() - Read one char from buffer (blocking)
 *   keyboard_haskey()  - Check if buffer has data
 */
