/* NullOS VGA Text Mode Driver
 *
 * 80x25 color text mode. Frame buffer at 0xB8000.
 * Each cell: 2 bytes (character + attribute).
 *
 * See: docs/PHASES.md Phase 2.1
 */

/* TODO: Implement VGA driver
 *
 * Constants:
 *   VGA_WIDTH  = 80
 *   VGA_HEIGHT = 25
 *   VGA_MEMORY = 0xB8000
 *
 * Functions:
 *   vga_init()           - Clear screen, reset cursor
 *   vga_putchar(char c)  - Print character, handle \n and scrolling
 *   vga_puts(const char *str) - Print string
 *   vga_set_color(uint8_t fg, uint8_t bg) - Set text colors
 *   vga_clear()          - Clear screen
 *   vga_set_cursor(int row, int col) - Move hardware cursor
 *
 * Scrolling:
 *   When cursor.row >= VGA_HEIGHT, memmove rows up and clear last row.
 *
 * Hardware cursor:
 *   Write to VGA I/O ports 0x3D4 / 0x3D5
 */
