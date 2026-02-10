; NullOS Stage 1 Bootloader
; -------------------------
; Loaded by BIOS to 0x7C00. Exactly 512 bytes.
; Loads Stage 2 from disk and jumps to it.
;
; See: docs/PHASES.md Phase 1.1

[BITS 16]
[ORG 0x7C00]

; TODO: Implement Stage 1
; 1. Set up segment registers (DS=ES=SS=0)
; 2. Set up stack (SP=0x7C00, grows downward)
; 3. Save boot drive number (DL)
; 4. Load Stage 2 sectors from disk using BIOS int 0x13
; 5. Jump to Stage 2 entry point

jmp $                       ; Infinite loop (placeholder)

; Pad to 510 bytes and add boot signature
times 510 - ($ - $$) db 0
dw 0xAA55
