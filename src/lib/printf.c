/* NullOS Minimal Printf
 *
 * Supports: %d, %u, %x, %s, %c, %p, %%.
 * Outputs via VGA text mode (and optionally serial).
 */

/* TODO: Implement printf
 *
 * Uses <stdarg.h> (our own freestanding version) for variadic arguments.
 *
 * Functions:
 *   int kprintf(const char *fmt, ...);          - Print to VGA
 *   int ksprintf(char *buf, const char *fmt, ...); - Print to buffer
 *
 * Format specifiers:
 *   %d / %i  - Signed decimal
 *   %u       - Unsigned decimal
 *   %x / %X  - Hexadecimal
 *   %s       - String
 *   %c       - Character
 *   %p       - Pointer (hex with 0x prefix)
 *   %%       - Literal percent
 *
 * Width and zero-padding: %08x, %10d, etc.
 */
