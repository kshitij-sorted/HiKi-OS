BITS 16
ORG 0x7C00

start:
    ; Print message
    mov ah, 0x0E
    mov si, message
.print_char:
    lodsb
    or al, al
    jz .done
    int 0x10
    jmp .print_char
.done:

    ; Load kernel (assume it's 1 sector and starts at LBA 1)
    mov ah, 0x02       ; BIOS read sector function
    mov al, 1          ; Number of sectors to read
    mov ch, 0          ; Cylinder 0
    mov cl, 2          ; Sector 2 (sector numbers start at 1)
    mov dh, 0          ; Head 0
    mov dl, 0x00       ; Drive 0 (floppy/hard disk)
    mov bx, 0x1000     ; Load segment:offset = 0x0000:0x1000
    mov es, bx
    xor bx, bx         ; Offset = 0
    int 0x13
    jc disk_error      ; Jump if carry set (disk error)

    ; Jump to loaded kernel
    jmp 0x1000:0x0000

disk_error:
    mov si, disk_fail_msg
    call print
    jmp $

print:
    mov ah, 0x0E
.print_loop:
    lodsb
    or al, al
    jz .print_done
    int 0x10
    jmp .print_loop
.print_done:
    ret

message db "HiKiOs Bootloader: Loading kernel...", 0
disk_fail_msg db "Disk read error!", 0

times 510 - ($ - $$) db 0
dw 0xAA55

