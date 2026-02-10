; NullOS Stage 2 Bootloader
; -------------------------
; Handles real mode setup, A20 enablement, GDT load,
; protected mode switch, and jump to kernel.
;
; See: docs/PHASES.md Phase 1.2

[BITS 16]

; TODO: Implement Stage 2
; 1. Detect memory map (int 0x15, EAX=0xE820)
; 2. Call a20_enable (a20.asm)
; 3. Load GDT (gdt.asm)
; 4. Enter protected mode (set CR0.PE)
; 5. Far jump to 32-bit code segment
; 6. Set up 32-bit segment registers and stack
; 7. Jump to kernel entry at 0x100000

[BITS 32]
; Protected mode entry point

; TODO: Set DS, ES, FS, GS, SS to 0x10 (data segment)
; TODO: Set up stack in high memory
; TODO: Jump to _start (kernel entry)

jmp $                       ; Infinite loop (placeholder)
