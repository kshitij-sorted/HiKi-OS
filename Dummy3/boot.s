; boot.S - BIOS bootloader (512 bytes)
BITS 16
ORG 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    ; Load kernel from sector 2 into 0x1000:0000
    mov ax, 0x1000
    mov es, ax
    xor bx, bx
    mov ah, 0x02         ; BIOS read sectors
    mov al, 20            ; read 20 sectors
    mov ch, 0            ; cylinder
    mov cl, 2            ; sector (starts at 1)
    mov dh, 0            ; head
    ; DL already contains boot drive number
    int 0x13

    jc disk_error

    jmp 0x1000:0x0000

disk_error:
    mov si, disk_error_msg
.print:
    lodsb
    or al, al
    jz .halt
    mov ah, 0x0E
    int 0x10
    jmp .print

.halt:
    hlt
    jmp .halt

disk_error_msg db "Disk read error!", 0

TIMES 510-($-$$) db 0
DW 0xAA55
