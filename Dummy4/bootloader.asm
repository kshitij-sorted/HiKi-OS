; bootloader.asm
; NASM flat binary bootloader

BITS 16
ORG 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Read 30 sectors starting at LBA sector 1 into memory at 0x1000
    mov bx, 0x1000        ; load address
    mov cx, 1             ; starting sector (LBA sector 1)
    mov dx, 0x80          ; drive number (first hard disk)

    mov si, 0             ; sector counter

read_loop:
    push si               ; save sector count

    mov ah, 0x02          ; BIOS read sector function
    mov al, 1             ; read one sector at a time
    mov ch, 0             ; cylinder 0
    mov dh, 0             ; head 0
    mov cl, byte [cx]     ; sector number low bits
    ; Using LBA requires more work; for simplicity we use CHS 0,0,sector

    mov dl, 0x80          ; boot drive (first HDD)
    int 0x13

    jc disk_error         ; jump if error

    add bx, 512           ; next 512-byte block
    inc si
    cmp si, 30
    jl read_loop

    pop si                ; restore sector count

    ; Setup GDT (2 entries: null + code/data)
gdt_start:
    dw 0
    dw 0
    db 0
    db 0
    db 0
    db 0

gdt_code:
    dw 0xFFFF
    dw 0
    db 0
    db 0x9A
    db 0xCF
    db 0

gdt_data:
    dw 0xFFFF
    dw 0
    db 0
    db 0x92
    db 0xCF
    db 0

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

gdt_end:

    ; Load GDT
    lgdt [gdt_descriptor]

    ; Enable protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Far jump to flush prefetch and load CS
    jmp 0x08:protected_mode_entry

; 32-bit protected mode code
[BITS 32]
protected_mode_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x90000    ; set up stack

    ; Jump to kernel at 0x1000
    jmp 0x08:0x1000

disk_error:
    ; Print error (not implemented)
    cli
    hlt

times 510 - ($-$$) db 0
dw 0xAA55
