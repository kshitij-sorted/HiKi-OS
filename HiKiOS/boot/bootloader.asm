BITS 16
ORG 0x7C00

start:
    ; Clear screen (optional)
    mov ah, 0x0E
    mov si, message
.print_char:
    lodsb
    or al, al
    jz .done
    int 0x10
    jmp .print_char
.done:

    ; Hang
.halt:
    cli
    hlt
    jmp .halt

message db "HiKiOs Bootloader started...", 0

; Padding to 510 bytes
times 510 - ($ - $$) db 0
dw 0xAA55  ; Boot signature
