/* NullOS PIT Timer Driver
 *
 * Programmable Interval Timer on IRQ 0 (interrupt 32).
 * Configured for 100 Hz (10ms ticks).
 *
 * See: docs/PHASES.md Phase 2.5
 */

/* TODO: Implement PIT timer
 *
 * PIT base frequency: 1,193,180 Hz
 * Divisor for 100 Hz: 1193180 / 100 = 11932
 *
 * Configuration:
 *   outb(0x43, 0x36);              // Channel 0, lobyte/hibyte, rate generator
 *   outb(0x40, divisor & 0xFF);    // Low byte
 *   outb(0x40, divisor >> 8);      // High byte
 *
 * Functions:
 *   timer_init(uint32_t freq)  - Configure PIT frequency
 *   timer_handler()            - Increment tick counter
 *   timer_get_ticks()          - Return current tick count
 *   timer_sleep(uint32_t ms)   - Busy-wait for N milliseconds
 */
