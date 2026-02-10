/* NullOS VGA Text Mode Driver
 *
 * 80x25 color text mode. Frame buffer at 0xB8000.
 * Each cell: 2 bytes (character + attribute).
 *
 * See: docs/PHASES.md Phase 2.1
 */

#include <kernel/vga.h>
#include <lib/string.h>
#include <stdint.h>

/* VGA constants */
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((uint16_t *)0xB8000)

/* Color constants */
#define VGA_BLACK 0
#define VGA_BLUE 1
#define VGA_GREEN 2
#define VGA_CYAN 3
#define VGA_RED 4
#define VGA_MAGENTA 5
#define VGA_BROWN 6
#define VGA_WHITE 7

/* VGA state */
static int vga_row = 0;
static int vga_col = 0;
static uint8_t vga_color = (VGA_WHITE << 4) | VGA_BLACK;

/* Make color attribute byte */
static inline uint8_t vga_make_color(uint8_t fg, uint8_t bg) {
    return (bg << 4) | fg;
}

/* Make VGA entry (character + color) */
static inline uint16_t vga_entry(uint8_t uc, uint8_t color) {
    return ((uint16_t)uc << 8) | color;
}

/* Update hardware cursor */
static void vga_update_cursor(void) {
    uint16_t pos = vga_row * VGA_WIDTH + vga_col;
    
    /* Set high byte of cursor position */
    __asm__ volatile("outb %0, $0x3D4" : : "a"(0x0E));
    __asm__ volatile("outb %0, $0x3D5" : : "a"((pos >> 8) & 0xFF));
    
    /* Set low byte of cursor position */
    __asm__ volatile("outb %0, $0x3D4" : : "a"(0x0F));
    __asm__ volatile("outb %0, $0x3D5" : : "a"(pos & 0xFF));
}

/* Clear the screen */
void vga_clear(void) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        VGA_MEMORY[i] = vga_entry(' ', vga_color);
    }
    vga_row = 0;
    vga_col = 0;
    vga_update_cursor();
}

/* Initialize VGA driver */
void vga_init(void) {
    vga_color = vga_make_color(VGA_WHITE, VGA_BLACK);
    vga_clear();
}

/* Set text color */
void vga_set_color(uint8_t fg, uint8_t bg) {
    vga_color = vga_make_color(fg, bg);
}

/* Put a single character */
void vga_putchar(char c) {
    if (c == '\n') {
        vga_col = 0;
        vga_row++;
    } else if (c == '\r') {
        vga_col = 0;
    } else {
        VGA_MEMORY[vga_row * VGA_WIDTH + vga_col] = vga_entry(c, vga_color);
        vga_col++;
    }
    
    /* Handle line wrap */
    if (vga_col >= VGA_WIDTH) {
        vga_col = 0;
        vga_row++;
    }
    
    /* Handle scrolling */
    if (vga_row >= VGA_HEIGHT) {
        /* Scroll up by moving rows */
        for (int i = 0; i < VGA_HEIGHT - 1; i++) {
            for (int j = 0; j < VGA_WIDTH; j++) {
                VGA_MEMORY[i * VGA_WIDTH + j] = 
                    VGA_MEMORY[(i + 1) * VGA_WIDTH + j];
            }
        }
        
        /* Clear bottom row */
        for (int j = 0; j < VGA_WIDTH; j++) {
            VGA_MEMORY[(VGA_HEIGHT - 1) * VGA_WIDTH + j] = 
                vga_entry(' ', vga_color);
        }
        
        vga_row = VGA_HEIGHT - 1;
    }
    
    vga_update_cursor();
}

/* Put a string */
void vga_puts(const char *str) {
    while (*str) {
        vga_putchar(*str);
        str++;
    }
}
